#pragma once
///////////////////////////////////////////////////////////////////////////
// FileHelpers.h - Helper class for file operations						 //
//																		 //
// Language:		C++, Visual Studio 2017                              //
// Application:		CSE687 - Object Oriented Design, Fall - 2018         //
// Author:			Jim Fawcett, CST 4-187, Syracuse University          //
//					(315) 443-3948, jfawcett@twcny.rr.com                //
///////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* -------------------
* This module provides functions to list the content of a directory and
* display chunk of text in a file.
*
* This package provide classes:
* --------------------
* showDirContents - List the files in a given directory.
* showFileLines - Display the chunk of text in a given file from given start to end line number.
*
*
* Required Files:
* ---------------
* Logger.h - Header file for logginf the message
* FileSystem.h - Header file for to support file and directory operations
*/
#include <iostream>
#include "FileSystem.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../test/ILogger.h"
#include <regex>

class FileHelpers
{
public:
	using Path = std::string;
	using Message = std::string;
	using Line = size_t;
	using File = std::string;
	using Files = std::vector<File>;

	static bool showDirContents(const Path& path, const Message& message, std::ostream& out = std::cout);
	static bool showFileLines(const Path& path, Line start, Line end, const Message& message, std::ostream& out = std::cout);
	static std::vector<std::string> listFiles(const Path& path, const std::string& fileNameRegex);

private:
	static std::string title(const std::string& title, const char underline = '=') {
		std::ostringstream out;
		out << "\n" << title;
		out << "\n" << std::string(title.size() + 2, underline);
		return out.str();
	}
};

//--------------< shows all the files in a directory with .cpp and .h extention >-----------------
inline bool FileHelpers::showDirContents(const Path& path, const Message& msg, std::ostream& out) {
	if (msg.size() > 0)
		out << title(msg);
	if (!FileSystem::Directory::exists(path)) {
		out << ("\n  path does not exist");
		return false;
	}


	Files files = FileSystem::Directory::getFiles(path);
	for (auto file : files) {
		std::string ext = FileSystem::Path::getExt(file);
		if (ext == "h" || ext == "cpp")
			out << "\n  " << file;
	}

	out << "\n";

	return true;
}

//----------------< display the chunck of lines in a given file given start and end line number >------------------
inline bool FileHelpers::showFileLines(const Path& path, Line start, Line end, const Message& msg, std::ostream& out) {
	if (msg.size() > 0)
		out << title(msg);
	out << "\n  " << FileSystem::Path::getFullFileSpec(path);

	std::ifstream file(path);
	if (!file.good()) {
		out << "\n  can't open file";
		return false;
	}

	std::string line;
	size_t count = 0;
	while (std::getline(file, line))
	{
		if (++count < start) continue;
		if (count > end) break;
		out << "\n  " << std::setw(4) << count << " " << line;
	}
	out << "\n";
	return true;
}

inline std::vector<std::string> FileHelpers::listFiles(const Path& path, const std::string& fileNameRegex) {
	std::vector<std::string> fileList;
	std::regex reg(fileNameRegex);

	if (!FileSystem::Directory::exists(path)) {
		return {};
	}

	Files files = FileSystem::Directory::getFiles(path);
	for (auto file : files) {
		std::string name = FileSystem::Path::getName(file);
		std::smatch match;
		if (std::regex_search(name, match, reg)) {
			//match found add the path to the file name
			fileList.push_back(path + "/" + name);
		}
	}

	//get the files for the directories within the path
	auto directories = FileSystem::Directory::getDirectories(path);
	for (auto directory : directories) {
		if (directory.compare(".") == 0 || directory.compare("..") == 0) continue;
		auto recFileList = listFiles(path + "/" + directory, fileNameRegex);
		// append the nested result to current path
		if (recFileList.size() > 0) fileList.insert(fileList.end(), recFileList.begin(), recFileList.end());
	}
	return fileList;
}
