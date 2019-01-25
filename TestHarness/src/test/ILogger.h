#pragma once
///////////////////////////////////////////////////////////////////////////
// ILogger.h - Support for Logging										 //
//																		 //
// Language:		C++, Visual Studio 2017                              //
// Application:		CSE687 - Object Oriented Design, Fall - 2018         //
// Author:			Pavan Nagathihalli Shankarappa, Syracuse University, //
//					pnagathi@syr.edu                                     //
///////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* -------------------
* This module provides the utility for Logging functinality.
*
* This package provide classes:
* --------------------
* ITest.h - Header file for ITest interface that is implemted by all the test cases.
* ILogger.h - Header file for ILogger interface to log the message.
*
Notes:
* ------
* - Designed to provide interfaces to perform the logging.
*
* Maintainence History:
* ---------------------
* Version 1.0 : 12th October 2018
* - First release
*/

#include <iostream>

//---------------------<Logger interface to add stream and write to registered streams>---------
class ILogger {
public:
	virtual void addStream(std::ostream* pStream) = 0;
	virtual void write(const std::string& text) = 0;
};

//---------------------<HostLogger interface to assist dll test to write to logger>---------
class IHostLogger {
public:
	virtual void write(const std::string& text) = 0;
};