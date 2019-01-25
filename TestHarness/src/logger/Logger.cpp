#include "Logger.h"

//----------------< add output streams to which logger should write to >------------
void Logger::addStream(std::ostream* pStream) {
	streams_.push_back(pStream);
}

//----------------< write the message into the registered streams >-----------------
void Logger::write(const std::string& text) {
	for (auto eachStream : streams_) {
		*eachStream << text;
	}
}


#ifdef LOGGER_TEST


#include <sstream>
#include <iostream>

int main() {
	Logger logger;
	logger.addStream(&std::cout);
	logger.write("Writing to the registered streams");
	return 0;
}

#endif