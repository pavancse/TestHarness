///////////////////////////////////////////////////////////////////////
// Peer2.cpp - main function file for Client1			             //
//                                                                   //
// Language:    C++, Visual Studio 2017                              //
// Application: CSE687 - Object Oriented Design, Fall - 2018         //
// Author:      Pavan Nagathihalli Shankarappa, Syracuse University, //
//              pnagathi@syr.edu                                     //
///////////////////////////////////////////////////////////////////////
/*
* Module Description:
* ------------------
* This module is acts a Client that will communicate with the main process
* by using comm. It will send test request DLL to the main process and
* receive the result from the client process.
*
*
* Maintainence History:
* ---------------------
* Version 1.0 - 14th November 2018
* -First release
*/


#include "../CppCommWithFileXfer/MsgPassingComm/Comm.h"
#include "../CppCommWithFileXfer/Message/Message.h"
#include <iostream>
#include <thread>
#include <functional>
#include "../CppCommWithFileXfer/Utilities/FileUtilities/FileUtilities.h"

using namespace MsgPassingCommunication;

//Constant static end point values
static const std::string CLIENT_HOST = "localhost";
static const int CLIENT_PORT = 8082;
static const std::string MAIN_HOST = "localhost";
static const int MAIN_PORT = 9001;

//----------------------< Send function that will post the given message to specified comm >----------------------
void sndMsgs(Comm& comm, Message& msg)
{
	std::cout << "\n  Peer2 posted message \"" << msg.name() << "\"";
	msg.show();
	comm.postMessage(msg);
}

//----------------------< Get function that is executed by a thread. On receiving any message it will decode and perform action based on the message command >----------------------
void getMsgs(Comm& comm)
{
	Message msg;
	while (true)
	{
		msg = comm.getMessage();
		std::cout << "\n  Peer2 recvd  message \"" << msg.name() << "\"";
		msg.show();
		if (msg.command() == "stop")
			break;
		else if (msg.command() == "testResult") { // testResult is the command for obtaining the test result sent by child process
			std::cout << "\n  Peer2 recvd Result ";
			//If the passed value is true then it will check for the result file
			if (msg.attributes()["passed"] == "true") {
				Utilities::displayFileContents("Result is ",
					comm.getSaveFilePath() + "/" + msg.file(), std::cout);
			}
			else {
				std::cout << "\n DLL execution failed ";
			}
		}
	}
}

//----------------------< main function that Client execution begins from this function when project is run >--------------------------
int main(int argc, char** argv) {
	//Set the console window title
	::SetConsoleTitle(L"Client 2");
	std::cout << "\n Peer 2 starting on " << CLIENT_HOST << ":" << CLIENT_PORT;

	//Defining the endpoint for comm channel and start the comm
	EndPoint epPeer(CLIENT_HOST, CLIENT_PORT);
	EndPoint epMain(MAIN_HOST, MAIN_PORT);
	Comm comm(epPeer, "Peer2");
	comm.start();

	//Set the save and send file path to store file, if the msg contains file sending 
	std::string savePath = comm.setSaveFilePath("Peer1");
	std::cout << "\n  saving files to \"" << savePath << "\"";
	std::string sendPath = comm.setSendFilePath("../Debug");
	std::cout << "\n  sending files from \"" << sendPath << "\"";

	//Send message to main requesting for testing the DLL file
	Message fileMsg;
	fileMsg.to(epMain);
	fileMsg.from(epPeer);
	fileMsg.name("Execute DLL Request");
	fileMsg.command("testDLL");
	fileMsg.value("sendingFile");
	fileMsg.file("Requirements.dll");
	sndMsgs(comm, fileMsg);

	//Get message method is executing by a thread
	std::function<void()> tproc = [&]() { getMsgs(comm); };
	std::thread tget(tproc);
	tget.join();

	//Stop the comm channel
	comm.stop();
	std::cin.get();
	//End of main function
	return 0;
}