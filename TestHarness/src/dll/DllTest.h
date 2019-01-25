#pragma once
///////////////////////////////////////////////////////////////////////////
// DllTest.h - Support for DLL test execution							 //
//																		 //
// Language:		C++, Visual Studio 2017                              //
// Application:		CSE687 - Object Oriented Design, Fall - 2018         //
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
* DllExecutive - A suite for executing multiple test cases from dll.
*			   - Provide method to load the DLL, extract the test cases from the DLL.
*			   - Execute the tests from the container.
*
Notes:
* ------
* - Provided methods to register the test cases for execution.
* - Provide a method to executes and record the test result.
*
* Required Files:
* ---------------
* Utilities.h - Header file for TestExecutive and TestExecutor interface.
*
*
* Maintainence History:
* ---------------------
* Version 1.0 : 12th October 2018
* - First release
*/

#include "../test/Utilities.h"
#include <Windows.h>

//-------------------< This will load the tests from the DLL, 
// executes tests from the container and determone the overall result>------------
class DllExecutive : public TestExecutive {
public:
	bool doTests(IHostLogger* logger);
	void registerPath(std::string& path);
private:
	std::vector<std::string> dllPaths;
};

//------------------< This will check all the DLL in the given path >--------------
class DllExecutor : public TestExecutive {
public:
	bool loadAndExtract(const std::string& dllPath);
	void unload();
	~DllExecutor();
private:
	HMODULE hmod;
};