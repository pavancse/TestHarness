#include "Utilities.h"
#include "ILogger.h"
#include "../utilities/Commons.h"

//----------------< this method will executes the test case in a try/catch block and log the result or message >----------------
bool TestExecutor::execute(ITest* ts, IHostLogger* logger) {
	bool result = false;
	//log the test execution begins 
	logger->write(MsgUtils::formatMsg(ts->testName(), ts->author(), "begin executing"));
	try {
		//invoke the test method of test class. 
		result = ts->test();

		//determine the result based on the test execution response
		std::string res = "Result - Passed\n";
		if (!result) {
			res = "Result - Failed\n";
		}
		logger->write(MsgUtils::formatMsg(ts->testName(), ts->author(), res));
	}
	catch (std::exception& ex) {
		//catch and record the exception if any test throws.
		std::ostringstream out;
		out << "Exception occured : " << ex.what() << "\n";
		logger->write(MsgUtils::formatMsg(ts->testName(), ts->author(), out.str()));
	}
	return result;
}


//---------------< method to register the test case >-----------------
void TestExecutive::registerTest(ITest* ts) {
	tests_.push_back(ts);
}

//--------------< remove all the test case from the container >------------------
void TestExecutive::clearTests() {
	tests_.clear();
}

//-------------< method that sequentially executes the test cases that were registered >------------------
bool TestExecutive::doTests(IHostLogger* logger) {
	TestExecutor tester;
	bool result = true;
	for (auto test : tests_) {
		test->setHostLogger(logger);
		bool tResult = tester.execute(test, logger);
		if (!tResult)
			result = false;
	}
	return result;
}


#ifdef TESTEXECUTIVE
#include "../Logger.h"


class DLL_DECL Success : public ITest {
public:
	bool test() {
		return true;
	}
	std::string author() {
		return "Boss";
	}
	std::string testName() {
		return "Success test case";
	}
	void setHostLogger(IHostLogger* logger) {}
};


int main() {

	Logger* logger = new Logger();
	logger->addStream(&std::cout);
	HostLogger* hostLogger = new HostLogger(logger);
	TestExecutive executive;
	Success* success = new Success();
	executive.registerTest(success);
	executive.doTests(hostLogger);
	return 0;
}

#endif