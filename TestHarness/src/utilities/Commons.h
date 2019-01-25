#pragma once
///////////////////////////////////////////////////////////////////////////
// Commons.h - Header file that contains commons utilities that can be 	 //
//			   used by all packages										 //
// Language:		C++, Visual Studio 2017                              //
// Application:		CSE687 - Object Oriented Design, Fall - 2018         //
// Author:			Pavan Nagathihalli Shankarappa, Syracuse University, //
//					pnagathi@syr.edu                                     //
///////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* -------------------
* This module provides time function to which retuens the current time in string
*
* This package provide classes:
* --------------------
* TimeUtils
*	getCurrentTime - Get the current time in a string
*
Notes:
* ------
* - This is a general package which contains functions that can be used 
*	by any packages which requires it.
*
*/
#include <string>
#include <time.h>
#include <sstream>

//---------------< TimeUtils namespace that contains function related to date time >--------------
namespace TimeUtils {

	//---------------< Returns current time string >-----------------
	inline std::string getCurrentTime() {
		char buff[26];
		struct tm tm;
		time_t t = time(nullptr);
		localtime_s(&tm, &t);
		strftime(buff, 26, "%c", &tm);
		return std::string(buff);
	}
}

namespace MsgUtils {
	//---------------< method to format the logger message >------------------
	inline std::string formatMsg(const std::string& testName, const std::string& author, const std::string& message) {
		std::ostringstream out;
		out << "\n" << TimeUtils::getCurrentTime() << " | " << testName << " | " + author << " | " << message << "\n";
		return out.str();
	}
}
