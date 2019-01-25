#pragma once
///////////////////////////////////////////////////////////////////////
// TestHarnessMain.h - main function file for Main process that	 //
//					will create and communicate with child process	 //
//                                                                   //
// Language:    C++, Visual Studio 2017                              //
// Application: CSE687 - Object Oriented Design, Fall - 2018         //
// Author:      Pavan Nagathihalli Shankarappa, Syracuse University, //
//              pnagathi@syr.edu                                     //
///////////////////////////////////////////////////////////////////////
/*
* Module Description:
* ------------------
* This module is Main process module. It will create child process on its start.
* It acts as an SPOC between client and the child processes. It will communicate
* with using messages through comm. It will spawn process and keep track them.
* If any child process quits, then based on the process exit code it will
* start the same process again. It will kepp track of the test request from clients
* and child ready process. When a child is ready and a test reqiest is received it
* will send test request message to child for testing.
*
*This package provide classes:
* --------------------
* TestHarnessMain - Create and monitor child process
*				  - Acts as interface between Child and Client
*
* Required Files:
* ---------------
* Process.h - To create child process
* Message.h - Message as a medium to send information to Child and Client
* Comm.h - Communication channel
* Cpp11-BlockingQueue.h - Blocking Queue's to store ready childs and test request messages

* Maintainence History:
* ---------------------
* Version 1.0 - 14th November 2018
* -First release
*/
#include "../Process/Process/Process.h"
#include "../CppCommWithFileXfer/Message/Message.h"
#include "../CppCommWithFileXfer/MsgPassingComm/Comm.h"
#include "../CppCommWithFileXfer/Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"
#include <vector>
#include <map>

using namespace MsgPassingCommunication;

//-------------------< This is the main process class >----------------------
class TestHarnessMain {
public:
	EndPoint epMain;
	void getMsgs(Comm& comm);
	void sndMsgs(Comm& comm, Message& msg);
	void start(Comm& comm);
	static void createProcess(int numProcessess);
	static void generateProcess(EndPoint ep);
	void stop(Comm& comm);
	Message getFiles(Message& msg);
	Message getDirs(Message& msg);
private:
	BlockingQueue<EndPoint> _processReadyQ;
	BlockingQueue<Message> _requestMsgQ;
	static std::map<std::string, Process> _processMap;
};