///////////////////////////////////////////////////////////////////////////
// Requirements.cpp - It contains class that demonstrates the		     //
//						project3 requirements							 //
//																		 //
// Language:		C++, Visual Studio 2017                              //
// Application:		CSE687 - Object Oriented Design, Fall - 2018         //
// Author:			Pavan Nagathihalli Shankarappa, Syracuse University, //
//					pnagathi@syr.edu                                     //
///////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* -------------------
* This module provide test class that test the requirements of the project.
*
* This package provide classes:
* --------------------
* TestHarnessReq1 - Test Requirement 1 of TestHarness Project
* TestHarnessReq2 - Test Requirement 2 of TestHarness Project
* TestHarnessReq3 - Test Requirement 3 of TestHarness Project
* TestHarnessReq4 - Test Requirement 4 of TestHarness Project
* TestHarnessReq5 - Test Requirement 5 of TestHarness Project
* TestHarnessReq6 - Test Requirement 6 of TestHarness Project
* TestHarnessReq7 - Test Requirement 7 of TestHarness Project
* TestHarnessReq8 - Test Requirement 8 of TestHarness Project
* TestHarnessReq9 - Test Requirement 9 of TestHarness Project
* TestHarnessReq10 - Test Requirement 10 of TestHarness Project
*
*
* Required Files:
* ---------------
* ITest.h - ITest interface
* ILogger.h - Logger to log the message
* FileUtilities.h - Utilicy class in file and directory access
*/

#include "../TestHarness/src/test/ILogger.h"
#include "../TestHarness/src/test/ITest.h"
#include <iostream>
#include <sstream>
#include "../CppCommWithFileXfer/Utilities/FileUtilities/FileUtilities.h"

using namespace Utilities;

//------------------< Requirement 1 demonstration >---------------------
class DLL_DECL Requirement1 : public ITest {
private:
	IHostLogger* logger;
public:
	bool test() {
		std::ostringstream stream;
		std::string msg = "Requirement 1 - Use of C++\n";
		Patterns patterns;
		patterns.push_back("*.cpp");
		patterns.push_back("*.h");
		showDirContents("../../../TestHarness/src", msg, patterns, stream);
		logger->write(stream.str());
		return true;
	}

	std::string author() {
		return "Patrick";
	}

	std::string testName() {
		return "Requirement 1";
	}

	void setHostLogger(IHostLogger* hostLogger) {
		logger = hostLogger;
	}
};

//------------------< Requirement 2 demonstration >---------------------
class DLL_DECL Requirement2 : public ITest {
private:
	IHostLogger* logger;
public:
	bool test() {
		std::ostringstream stream;
		std::string msg = "Requirement 2 - Use of New and Delete\n";
		showFileLines("../../../TestHarnessMain/TestHarnessMain.cpp", 67, 108, msg, stream);
		std::string output = stream.str();
		logger->write(output);
		return true;
	}

	std::string author() {
		return "Donald";
	}

	std::string testName() {
		return "Requirement 2";
	}

	void setHostLogger(IHostLogger* hostLogger) {
		logger = hostLogger;
	}
};

//------------------< Requirement 3 demonstration >---------------------
class DLL_DECL Requirement3 : public ITest {
private:
	IHostLogger* logger;
public:
	bool test() {
		std::ostringstream stream;
		std::string msg = "Requirement 3 - Client-Server Configuration\n";
		showFileLines("../../../GUI/MainWindow.xaml.cs", 120, 322, msg, stream);
		logger->write(stream.str());
		return true;
	}

	std::string author() {
		return "Michal";
	}

	std::string testName() {
		return "Requirement 3";
	}

	void setHostLogger(IHostLogger* hostLogger) {
		logger = hostLogger;
	}
};

//------------------< Requirement 4 demonstration >---------------------
class DLL_DECL Requirement4 : public ITest {
private:
	IHostLogger* logger;
public:
	bool test() {
		std::ostringstream stream;
		std::string msg = "Requirement 4 - Graphical User Interface\n";
		showFileLines("../../../GUI/MainWindow.xaml.cs", 180, 322, msg, stream);
		showFileLines("../../../GUI/MainWindow.xaml", 0, 40, msg, stream);
		logger->write(stream.str());
		return true;
	}

	std::string author() {
		return "Michal";
	}

	std::string testName() {
		return "Requirement 4";
	}

	void setHostLogger(IHostLogger* hostLogger) {
		logger = hostLogger;
	}
};



//------------------< Requirement 5 demonstration >---------------------
class DLL_DECL Requirement5 : public ITest {
private:
	IHostLogger* logger;
public:
	bool test() {
		std::ostringstream stream;
		std::string msg = "Requirement 5 - Message\n";
		showFileLines("../../../TestHarnessMain/TestHarnessMain.cpp", 6, 117, msg, stream);
		showFileLines("../../../TestHarness/src/TestHarness.cpp", 43, 127, msg, stream);
		logger->write(stream.str());
		return true;
	}

	std::string author() {
		return "Sam";
	}

	std::string testName() {
		return "Requirement 5";
	}

	void setHostLogger(IHostLogger* hostLogger) {
		logger = hostLogger;
	}
};


//------------------< Requirement 6 demonstration >---------------------
class DLL_DECL Requirement6 : public ITest {
private:
	IHostLogger* logger;
public:
	bool test() {
		std::ostringstream stream;
		std::string msg = "Requirement 5 - Use of logger in child process\n";
		showFileLines("../../../GUI/MainWindow.xaml.cs", 180, 322, msg, stream);
		logger->write(stream.str());
		return true;
	}

	std::string author() {
		return "Nikhil";
	}

	std::string testName() {
		return "Requirement 6";
	}

	void setHostLogger(IHostLogger* hostLogger) {
		logger = hostLogger;
	}
};

//------------------< Requirement 7 demonstration >---------------------
class DLL_DECL Requirement7 : public ITest {
private:
	IHostLogger* logger;
public:
	bool test() {
		std::ostringstream stream;
		std::string msg = "Requirement 7 - Process Pool Child\n";
		showFileLines("../../../TestHarnessMain/TestHarnessMain.cpp", 6, 187, msg, stream);
		showFileLines("../../../TestHarness/src/TestHarness.cpp", 43, 171, msg, stream);
		logger->write(stream.str());
		return true;
	}

	std::string author() {
		return "Ramsey";
	}

	std::string testName() {
		return "Requirement 7";
	}

	void setHostLogger(IHostLogger* hostLogger) {
		logger = hostLogger;
	}
};

//------------------< Requirement8 demonstration >---------------------
class DLL_DECL Requirement8 : public ITest {
private:
	IHostLogger* logger;
public:
	bool test() {
		std::ostringstream stream;
		std::string msg = "Requirement 8 - Child Send Result\n";
		showFileLines("../../../TestHarness/src/TestHarness.cpp", 61, 107, msg, stream);
		logger->write(stream.str());
		return true;
	}

	std::string author() {
		return "Patrick";
	}

	std::string testName() {
		return "Requirement 8";
	}

	void setHostLogger(IHostLogger* hostLogger) {
		logger = hostLogger;
	}
};

//------------------< Requirement9 demonstration >---------------------
class DLL_DECL Requirement9 : public ITest {
private:
	IHostLogger* logger;
public:
	bool test() {
		std::ostringstream stream;
		std::string msg = "Requirement 9 - Two or more child\n";
		showFileLines("../../../GUI/MainWindow.xaml.cs", 49, 260, msg, stream);
		logger->write(stream.str());
		return true;
	}

	std::string author() {
		return "Jack";
	}

	std::string testName() {
		return "Requirement 9";
	}

	void setHostLogger(IHostLogger* hostLogger) {
		logger = hostLogger;
	}
};


//------------------< Requirement10 demonstration >---------------------
class DLL_DECL Requirement10 : public ITest {
private:
	IHostLogger* logger;
public:
	bool test() {
		std::ostringstream stream;
		std::string msg = "Requirement 10 - Requirements\n";
		showFileLines("../../../Requirements/Requirements.cpp", 41, 337, msg, stream);
		logger->write(stream.str());
		return true;
	}

	std::string author() {
		return "Dorsey";
	}

	std::string testName() {
		return "Requirement 10";
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
		_testList.push_back(new Requirement1());
		_testList.push_back(new Requirement2());
		_testList.push_back(new Requirement3());
		_testList.push_back(new Requirement4());
		_testList.push_back(new Requirement5());
		_testList.push_back(new Requirement6());
		_testList.push_back(new Requirement7());
		_testList.push_back(new Requirement8());
		_testList.push_back(new Requirement9());
		_testList.push_back(new Requirement10());
		return _testList;
	}
};

//---------------< It will return the object to CodeUtilitiesTests that is created in the heap >---------
DLL_DECL ITests* getITests() {
	return new CodeUtilitiesTests();
}