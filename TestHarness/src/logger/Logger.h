#pragma once
///////////////////////////////////////////////////////////////////////////
// Logger.h - Module to log messages									 //
//																		 //
// Language:		C++, Visual Studio 2017                              //
// Application:		CSE687 - Object Oriented Design, Fall - 2018         //
// Author:			Pavan Nagathihalli Shankarappa, Syracuse University, //
//					pnagathi@syr.edu                                     //
///////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* -------------------
* This module provides a class to log the messages to one or more output streams.
* HostLogger is an implementation of IHostLogger. This provide the test in dll 
* use logger to log the message.
*	
* This package provide classes:
* --------------------
* Logger - Logger class that provides method to write into the output streams 
*		   which were registered.
* HostLogger - It hava a reference to the Logger instance and write method to 
*			log the message.
*
*
* Maintainence History:
* ---------------------
* Version 1.1 - 12th October 2018
* - Logger implements ILogger interface.
* - HostLogger implements IHostedLogger to help test case log.
* Version 1.0 - 22nd September 2018
* - First release
*
*/

#include <iostream>
#include <vector>
#include "../test/ILogger.h"
#include <fstream>
#include <string>

//------------------< Logger class is the implementation of ILogger interface>----------
class Logger : public ILogger {
public:
	void addStream(std::ostream* pStream);
	void write(const std::string& text);
private:
	//----------------< container to store all streams >-----------------
	std::vector<std::ostream*> streams_;
};

//-------------------< HostLogger class is the implementation of IHostLogger interface>-----------
class HostLogger : public IHostLogger {
public:
	HostLogger(Logger* logger) : logger(logger) {}
	void write(const std::string& text) {
		logger->write(text);
	}
	void addStream(std::ostream* stream) {
		logger->addStream(stream);
	}
private:
	//Instance of logger
	Logger *logger;
};