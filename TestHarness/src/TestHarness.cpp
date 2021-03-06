///////////////////////////////////////////////////////////////////////
// TestHarness.cpp - main function file for test harness             //
//                                                                   //
// Language:    C++, Visual Studio 2017                              //
// Application: CSE687 - Object Oriented Design, Fall - 2018         //
// Author:      Pavan Nagathihalli Shankarappa, Syracuse University, //
//              pnagathi@syr.edu                                     //
///////////////////////////////////////////////////////////////////////
/*
* Module Description:
* ------------------
* This module is used to create child process. The Main process will use this module
* exe file for starting a new process. It will receive the communication information 
* as command line arguments. Once the child process is ready, it will notify the main
* process. If the main have received any test DLL request, then main will send message
* informing the execution of the file. This module will load the DLL and execute the 
* test cases as per Single User TestHarness. Once all the test execution completed,
* it will send the result back to client which had requested main process for the execution.
* Once the result is sent, the client will be ready again by posting ready message to 
* the main process.
*
*
* Maintainence History:
* ---------------------
* Version 1.1 - 14th November 2018
* - Communication using Comm and executing DLL.
* - Act as a child process.
*
* Version 1.0 - 7th November 2018
* -First release
*/
#define _WINSOCKAPI_
#include "test/Utilities.h"
#include <iostream>
#include <fstream>
#include "logger/Logger.h"
#include "utilities/FileHelpers.h"
#include "dll/DllTest.h"
#include "../../CppCommWithFileXfer/MsgPassingComm/Comm.h"
#include "../../CppCommWithFileXfer/Message/Message.h"

using namespace MsgPassingCommunication;
EndPoint epMain, epChild;

//----------------------< Send function that will post the given message to specified comm >----------------------
void sndMsgs(Comm& comm, Message& msg) {
	std::cout << "\n Child posted message \"" << msg.name() << "\"";
	msg.show();
	comm.postMessage(msg);
}

//----------------------< Report function that will report to main process as child is ready to perform testing >----------------------
void reportMain(Comm& comm) {
	Message msg;
	msg.from(epChild);
	msg.to(epMain);
	msg.name("Report ready");
	msg.command("ready");
	sndMsgs(comm, msg);
}

//----------------------< Function that will load the DLL file, execute all the test cases in it and send test result back to the client >----------------------
void executeDLL(Comm& comm, std::string fileName, EndPoint& epClient) {
	//Pass the path of the DLL file to the DllExecutive
	DllExecutive ex;

	//DLL file path
	std::string path = comm.getSendFilePath() + fileName;
	ex.registerPath(path);
	std::cout << "Executing DLL " << path;

	//Create a logger instance to record the test message and result.
	Logger logger;

	//Register logger in hostlogger
	HostLogger hostLogger(&logger);

	std::string logFileSpec = path + "-LogFile.txt";

	hostLogger.addStream(&std::cout);

	std::ofstream fileStream(logFileSpec, std::ios::out);
	if (fileStream.good())
		hostLogger.addStream(&fileStream);

	//Single function to which executes all the tests and returns the overall result.
	bool result = ex.doTests(&hostLogger);

	//Closing the file stream before send result back to client
	fileStream.close();
	
	//Send test result message to Client
	Message msg;
	msg.command("getResults");
	msg.name("DLLtestresult");
	msg.attributes()["file"] = logFileSpec;
	msg.attributes()["passed"] = "false";
	if (result) {
		msg.attributes()["passed"] = "true";
	}
	msg.to(epClient);
	sndMsgs(comm, msg);

	//Report to main saying the client is ready again for testing
	reportMain(comm);
}

//----------------------< Get function that is executed by a thread. On receiving any message it will decode and perform action based on the message command >----------------------
void getMsgs(Comm& comm)
{
	Message msg;
	while (true) {
		msg = comm.getMessage();
		std::cout << "\n Child recvd message \"" << msg.name() << "\"";
		msg.show();
		if (msg.command() == "stop") {
			break;
		}
		else if (msg.command() == "testDLL") {	// testDLL is the command for executing the DLL file
			//Extract client end point from the message for later usage
			EndPoint epClient(msg.from().address, msg.from().port);
			executeDLL(comm, msg.file(), epClient);
		}
	}
}


//----------------------< main function that test harness execution begins from this function when project is run >--------------------------
int main(int argc, char** argv)
{	 
	if (argc < 5) {
		std::cout << "Main/child process hostname or post missing\n";
		std::cin.get();
		return 0;
	}

	std::cout << "\n Child process starting on " << argv[2] << ":" << argv[3];
	
	//Creating global endpoints for main and child
	epMain = EndPoint(argv[0], std::stoi(argv[1]));
	epChild = EndPoint(argv[2], std::stoi(argv[3]));

	std::string name = argv[4];
	//Set console title
	::SetConsoleTitle(name.c_str());
	

	Comm comm(epChild, name);
	std::string savePath = comm.setSaveFilePath(name+"\\");
	std::cout << "\n  saving files to \"" << savePath << "\"";
	std::string sendPath = comm.setSendFilePath(name+"\\");
	std::cout << "\n  sending files from \"" << sendPath << "\"";
	comm.start();

	//Report to main saying client is ready for execution
	reportMain(comm);

	//Start a thread that will execute get message function
	std::function<void()> tproc = [&]() { getMsgs(comm); };
	std::thread tget(tproc);
	tget.join();

	std::cin.get();
	//Stop the comm channel
	comm.stop();

	//End of main function successfully
	return 0;
}

