#pragma once
///////////////////////////////////////////////////////////////////////////
// ITest.h - Support for test declarion									 //
//																		 //
// Language:		C++, Visual Studio 2017                              //
// Application:		CSE687 - Object Oriented Design, Fall - 2018         //
// Author:			Pavan Nagathihalli Shankarappa, Syracuse University, //
//					pnagathi@syr.edu                                     //
///////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* -------------------
* This module provides the utility for creating test cases.
*
* This package provide classes:
* --------------------
* ITest - Interface for implementing tests.
*
Notes:
* ------
* - Designed to provide interface that will be implemented by classes that
*	would like to perform the testing.
*
* Required Files:
* ---------------
* ILogger.h - Header file for ILogger interface to log the message.
*
*
* Maintainence History:
* ---------------------
* Version 1.1 : 12th Oct 2018
* - ITest have author, testName and setHostLogger new methods.
*
* Version 1.0 : 22nd September 2018
* - First release
*/

#include <iostream>
#include <string>
#include <vector>
#include "ILogger.h"

#ifdef IN_DLL 
#define DLL_DECL __declspec(dllexport)
#else
#define DLL_DECL __declspec(dllimport)
#endif

//-------------------< Interface that all test will implement >-------------------
class DLL_DECL ITest {
public:
	virtual bool test() = 0;
	virtual std::string author() = 0;
	virtual std::string testName() = 0;
	virtual void setHostLogger(IHostLogger* logger) = 0;
};

//-------------------< Container that provides list of test cases to execute>-------------------
class DLL_DECL ITests {
public:
	virtual std::vector<ITest*> getTestList() = 0;
};

//-------------------< Interface to access testslist from DLL>-------------------
extern "C" {
	DLL_DECL ITests* getITests();
};