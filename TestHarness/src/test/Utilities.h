#pragma once
///////////////////////////////////////////////////////////////////////////
// Utilities.h - Support for test execution								 //
//																		 //
// Language:		C++, Visual Studio 2017                              //
// Application:		CSE687 - Object Oriented Design, Fall - 2018         //
// Source Author:	Jim Fawcett, CST 4-187, Syracuse University          //
//					(315) 443-3948, jfawcett@twcny.rr.com                //
// Author:			Pavan Nagathihalli Shankarappa, Syracuse University, //
//					pnagathi@syr.edu                                     //
///////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* -------------------
* This module provides the utility for registering and executing test cases.
*
* This package provide classes:
* --------------------
* TestExecutive - A suite for executing multiple test cases.
* TestExecutor - A test executor for individual test case.
*
Notes:
* ------
* - Provided methods to register the test cases for execution.
* - Provide a method to executes and record the test result.
*
* Required Files:
* ---------------
* ITest.h - Header file for ITest interface that is implemted by all the test cases.
* ILogger.h - Header file for ILogger interface to log the message.
*
*
* Maintainence History:
* ---------------------
* Version 1.1 : 12th Oct 2018
* - doTests method now have reference to IHostLogger
*
* Version 1.0 : 22nd September 2018
* - First release
*/

#include <iostream>
#include <string>
#include <vector>
#include "ITest.h"
#include "ILogger.h"


//-------------------< TestExecutor class that provide function to execute the each test >-----------------
class TestExecutor {
public:
	bool execute(ITest* testItem, IHostLogger* logger);
};


//---------------< TestExecutive is a class that provide container to process all tests >-------------
class TestExecutive {
public:
		
	using Tests = std::vector<ITest*>;
	bool doTests(IHostLogger* logger);
	void registerTest(ITest* ts);
	void clearTests();	
private:
	Tests tests_;
};