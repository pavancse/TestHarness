///////////////////////////////////////////////////////////////////////////
// CodeUtilitiesTest.h - Tests all the class in the CodeUtilities.h		 //
//																		 //
// Language:		C++, Visual Studio 2017                              //
// Application:		CSE687 - Object Oriented Design, Fall - 2018         //
// Author:			Pavan Nagathihalli Shankarappa, Syracuse University, //
//					pnagathi@syr.edu                                     //
///////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* -------------------
* This module implementes all the test class for the class that is in the CodeUtilities.h
*
* This package provide classes:
* --------------------
* ConverterTest - Test class for Converter class which is in CodeUtilities.h
* PersistFactoryTest - Test class for PersistFactory class which is in CodeUtilities.h
* BoxTest - Test class for Box class which is in CodeUtilities.h
* ProcessCommandLineTest - Test class for ProcessCommandLine class which is in CodeUtilities.h
*
Notes:
* ------
* - All the classes that would like to perform testing will implement ITest interface.
* - The class will override the test method to perform testing return the result.
*
* Required Files:
* ---------------
* ILogger.h - Logger interface
* ITest.h - ITest interface class
* CodeUtilities.h - Header file that contains classes that needs to be tested.
*/

#include "CodeUtilities.h"
#include "../../TestHarness/src/test/ILogger.h"
#include "../../TestHarness/src/test/ITest.h"
#include <iostream>
#include <cstring>

using namespace Utilities;

//------------------< Test for the converter class in CodeUtilities.h >---------------------
// - Converts the integer number to string and compare converted string with int value.
class DLL_DECL ConverterTest : public ITest {
private:
	IHostLogger* logger;
public:
	bool test() {
		const int number = 687;
		logger->write("\nValue of number : " + std::to_string(number));
		std::string numberStr = Converter<int>::toString(number);
		logger->write("\nValue of string after conversion : " + numberStr);
		return !numberStr.compare("687") && Converter<int>::toValue(numberStr) == number;
	}

	std::string author() {
		return "Mickey";
	}

	std::string testName() {
		return "BoxTest for value check";
	}

	void setHostLogger(IHostLogger* hostLogger) {
		logger = hostLogger;
	}
};

//------------------< Test for the PersistFactory class in CodeUtilities.h >---------------------
// - It will test for wrraped type holds the actual value and even on operator operation.
class DLL_DECL PersistFactoryTest : public ITest {
private:
	IHostLogger* logger;
public:
	bool test() {
		const double number = 6.87;
		logger->write("\nInitial value of the number : " + std::to_string(number));
		PersistFactory<Box<double>> value = Box<double>(number);
		value *= 2;
		logger->write("\nDouble value of the number : " + std::to_string(value));
		return value == 2 * number;
	}

	std::string author() {
		return "Donald";
	}

	std::string testName() {
		return "Converter for conversion check";
	}

	void setHostLogger(IHostLogger* hostLogger) {
		logger = hostLogger;
	}
};

//------------------< Test for the Box class in CodeUtilities.h >---------------------
// - It will wrraped the given number and checks whether the wrapped class holds the actual value.
class DLL_DECL BoxTest : public ITest {
private:
	IHostLogger* logger;
public:
	bool test() {
		const double pi = 3.14152;
		logger->write("\nBefore boxing the value " + std::to_string(pi));
		Box<double> boxedValue = pi;
		logger->write("\nBefore boxing the value " + std::to_string(boxedValue));
		return boxedValue == pi;
	}

	std::string author() {
		return "Adam";
	}

	std::string testName() {
		return "PersistFactory for operator check";
	}

	void setHostLogger(IHostLogger* hostLogger) {
		logger = hostLogger;
	}
};

//------------------< Test for the ProcessCommandLine class in CodeUtilities.h >---------------------
// - Tests whether it will display correct path that is passed in argv.
class DLL_DECL ProcessCommandLineTest : public ITest {
private:
	IHostLogger* logger;
public:
	bool test() {
		const int SIZE = 10;
		int argc = 2;
		char ** argv = new char*[argc];
		argv[0] = new char[SIZE];
		argv[1] = new char[SIZE];
		strcpy_s(argv[0], SIZE, "OOD");
		strcpy_s(argv[1], SIZE, "C++");

		std::ostringstream out;
		ProcessCmdLine cmdLine{ argc, argv, out };

		logger->write("\nBefore option added: " + out.str());
		cmdLine.option(97);
		cmdLine.showOptions();
		logger->write("\nAfter option added : " + out.str());

		delete argv[0];
		delete argv[1];
		delete[] argv;
		return out.str().compare("//a ");
	}

	std::string author() {
		return "John";
	}

	std::string testName() {
		return "Checking process command line";
	}

	void setHostLogger(IHostLogger* hostLogger) {
		logger = hostLogger;
	}
};


//----------------<This class provide a method that returns a list of ITest pointers to test cases >-----
class DLL_DECL CodeUtilitiesTests : public ITests {
public:
	std::vector<ITest*> getTestList() {
		std::vector<ITest*> _testList;
		_testList.push_back(new BoxTest());
		_testList.push_back(new ConverterTest());
		_testList.push_back(new PersistFactoryTest());
		_testList.push_back(new ProcessCommandLineTest());
		return _testList;
	}
};

//---------------< It will return the object to CodeUtilitiesTests that is created in the heap >---------
DLL_DECL ITests* getITests() {
	return new CodeUtilitiesTests();
}