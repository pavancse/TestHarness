//Include the header files
#include "../CppCommWithFileXfer/MsgPassingComm/Comm.h"
#include "TestHarnessMain.h"
#include "../CppCommWithFileXfer/Utilities/FileSystem/FileSystem.h"

using namespace MsgPassingCommunication;
std::map<std::string, Process> TestHarnessMain::_processMap;

//Constant static values
static int INITIAL_PROCESS_PORT = 9080;
static const std::string MAIN_HOST = "localhost";
static const int MAIN_PORT = 9001;
static const int DEFAULT_NUM_CHILD_PROCESS = 2;

//----------------------< Get function that is executed by a thread. On receiving any message it will decode and perform action based on the message command >----------------------
void TestHarnessMain::getMsgs(Comm& comm)
{
	Message msg;
	while (true) {
		msg = comm.getMessage();
		std::cout << "\n Main recvd message \"" << msg.name() << "\"";
		msg.show();
		if (msg.command() == "stop") {
			break;
		}
		else if (msg.command() == "ready") { // ready is the command for storing child process info
			_processReadyQ.enQ(msg.from());
		}
		else if (msg.command() == "testDLL") {  //testDLL is the command for storing messages from client
			_requestMsgQ.enQ(msg);
		}
		else if (msg.command() == "getDirs") { //getDirs to get all the directories
			msg = getDirs(msg);
			sndMsgs(comm, msg);
		}
		else if (msg.command() == "getFiles") { //getFiles to get all the files
			msg = getFiles(msg);
			sndMsgs(comm, msg);
		}
		////When child is ready and request is prending to test, assign the request to the ready child
		if (_requestMsgQ.size() > 0 && _processReadyQ.size() > 0) {
			Message reqMsg = _requestMsgQ.deQ();
			EndPoint epChild = _processReadyQ.deQ();
			reqMsg.to(epChild);
			reqMsg.show();
			reqMsg.value("sendingFile");
			reqMsg.file(reqMsg.attributes()["file"]);
			//Send test request message to ready child
			sndMsgs(comm, reqMsg);
		}
	}
}

//----------------------< get all the directories >----------------------
Message TestHarnessMain::getDirs(Message& msg) {
	Message reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("getDirs");
	std::string path = msg.value("path");
	if (path != "")
	{
		std::string searchPath = ".";
		if (path != ".")
			searchPath = searchPath + "\\" + path;
		std::vector<std::string> dirs = FileSystem::Directory::getDirectories(searchPath);
		size_t count = 0;
		for (auto item : dirs)
		{
			if (item != ".." && item != ".")
			{
				std::string countStr = Utilities::Converter<size_t>::toString(++count);
				reply.attribute("dir" + countStr, item);
			}
		}
	}
	else
	{
		std::cout << "\n  getDirs message did not define a path attribute";
	}
	return reply;
}

//----------------------< get all the files >----------------------
Message TestHarnessMain::getFiles(Message& msg) {
	Message reply;
	reply.to(msg.from());
	reply.from(msg.to());
	reply.command("getFiles");
	std::string path = msg.value("path");
	if (path != "")
	{
		std::string searchPath = ".";
		if (path != ".")
			searchPath = searchPath + "\\" + path;
		std::vector<std::string> files = FileSystem::Directory::getFiles(searchPath);
		size_t count = 0;
		for (auto item : files)
		{
			std::string countStr = Utilities::Converter<size_t>::toString(++count);
			reply.attribute("file" + countStr, item);
		}
	}
	else
	{
		std::cout << "\n  getFiles message did not define a path attribute";
	}
	return reply;
}

//----------------------< Send function that will post the given message to specified comm >----------------------
void TestHarnessMain::sndMsgs(Comm& comm, Message& msg) {
	std::cout << "\n Main posted message \"" << msg.name() << "\"";
	msg.show();
	comm.postMessage(msg);
}

//----------------------< start the main process >--------------------
void TestHarnessMain::start(Comm& comm) {
	//Spawn the default number of child processess
	createProcess(DEFAULT_NUM_CHILD_PROCESS);
}

//---------------------< Spawn the child process on start >----------------
void TestHarnessMain::createProcess(int numProcessess) {
	for (int i = 0; i < numProcessess; i++) {
		//Use unique port number for each child process
		EndPoint epProcess(MAIN_HOST, INITIAL_PROCESS_PORT++);
		TestHarnessMain::generateProcess(epProcess);
	}
}

//---------------------< Create a new child process by given end point info >-----------
void TestHarnessMain::generateProcess(EndPoint ep) {
	Process p;
	//Set the title of the process
	p.title("Process " + ep.port);

	//Set the application path the child should execute
	std::string appPath = "TestHarness.exe";
	p.application(appPath);

	//Set command line argument to run the application 
	std::ostringstream cmdLine;
	cmdLine << "localhost 9001 " << ep.address << " " << ep.port << " child" << ep.port;
	p.commandLine(cmdLine.str());

	std::cout << "\n  starting process: \"" << appPath << "\"";
	std::cout << "\n  with this cmdlne: \"" << cmdLine.str() << "\"";
	if (!p.create()) { //Create the process
		std::cout << "\n process generation failed \n";
		return;
	}

	//Callback function on child process exit
	CBP callback = []() { 
		std::cout << "\n Child process has quit \n";
		for (auto& it : _processMap) {
			if (!it.second.checkProcessAlive()) {
				EndPoint epClient = EndPoint::fromString(it.first);
				_processMap.erase(it.first);
				std::cout << "\n Quit process was running at : " << epClient.toString() << "\n Restarting child process \n";
				generateProcess(epClient);
				return;
			}
		}
	};
	//Set the call back function
	p.setCallBackProcessing(callback);
	p.registerCallback();
	//Store the child process information for spawning agin
	TestHarnessMain::_processMap[ep.toString()] = p;
	std::cout << "\n Child process started successfully \n";
}

//----------------< Stop the main process >------------------
void TestHarnessMain::stop(Comm& comm) {
	//Send stop message to all the created child process
	for (auto& it : _processMap) {
		Message msg;
		msg.to(EndPoint::fromString(it.first));
		msg.from(EndPoint(MAIN_HOST, MAIN_PORT));
		msg.command("stop");
		sndMsgs(comm, msg);
	}
}

//----------------------< main function that test harness main execution begins from this function when project is run >--------------------------
int main() {
	//Set the console window name
	::SetConsoleTitle(L"TestHarnessMain");
	std::cout << "\n Main starting on " << MAIN_HOST << ":" << MAIN_PORT;

	//Create the comm end point and start the comm
	EndPoint epMain(MAIN_HOST, MAIN_PORT);
	Comm comm(epMain, "main");
	comm.start();

	//Set the save ans send file path
	std::string savePath = comm.setSaveFilePath("main");
	std::cout << "\n  saving files to \"" << savePath << "\"";
	std::string sendPath = comm.setSendFilePath(".");
	std::cout << "\n  sending files from \"" << sendPath << "\"";
	
	//Create the object of the Main class
	TestHarnessMain main;

	//Start the main process execution
	main.start(comm);

	//Create thread that will execute the get message function
	std::function<void()> tproc = [&]() { main.getMsgs(comm); };
	std::thread tget(tproc);
	tget.join();

	//Stop the main process once execution completes
	main.stop(comm);

	//Stop the comm channel
	comm.stop();
	std::cin.get();
	//End of main function
	return 0;
}