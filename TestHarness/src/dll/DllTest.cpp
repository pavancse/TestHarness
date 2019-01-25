#include "DllTest.h"
#include <Windows.h>
#include "../utilities/FileHelpers.h"

//------<load and extract all the test cases from the given path>-----------------
bool DllExecutor::loadAndExtract(const std::string& dllPath) {
	//load dll
	hmod = LoadLibrary(dllPath.c_str());
	if (!hmod) return false;

	//get the reference of the method that will return the testcases
	using gIts = ITests * (*)();
	gIts tests = (gIts)GetProcAddress(hmod, "getITests");

	if (tests) {
		ITests* iTests = tests();
		if (!iTests) {
			return false;
		}
		//register all the tests from the returned list
		for (auto iTest : iTests->getTestList()) {
			registerTest(iTest);
		}
		return true;
	}
	return false;
}

//---------------< Unload the DLL >--------------
void DllExecutor::unload() {
	if (hmod) {
		std::cout << "\nUnload the Dll";
		FreeLibrary(hmod);
	}
}

//--------------< Distructor >--------------------
DllExecutor::~DllExecutor() {
	unload();
}

//--------------< find all the dlls and execute them one-by-one >------------
bool DllExecutive::doTests(IHostLogger* logger) {
	bool result = true;
	//iterate through all the DLL path
	for (std::string dllPath : dllPaths) {
		std::cout << "\nLoading Dll - " << dllPath << std::endl;
		DllExecutor executor;
		//Load the DLL and extract the test cases
		if (!executor.loadAndExtract(dllPath)) {
			std::cout << "\nLoading dll " << dllPath << " failed" << std::endl;
			result = false;
			continue;
		}
		//Determine the overall result based on test execution
		result |= executor.doTests(logger);
	}

	if (result) std::cout << "\nAll the tests in the Dll passed";
	else std::cout << "\nAtleast one of the test in the Dll failed";

	//Return the result
	return result;
}

//-------------< Regiter the DLL path that will store in the vector >-------------
void DllExecutive::registerPath(std::string& path) {
	dllPaths.push_back(path);
}

#ifdef TEST_DLL_UTILS
#include "../Logger.h"
int main() {

	Logger* logger = new Logger();
	logger->addStream(&std::cout);
	HostLogger* hostLogger = new HostLogger(logger);

	DllExecutor executor;
	executor.loadAndExtract("../../../x64/Debug/CodeUtilitiesTest.dll");
	executor.doTests(hostLogger);
	executor.unload();

	delete hostLogger;
	delete logger;

	return 0;
}

#endif