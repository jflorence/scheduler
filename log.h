#ifndef LOG_H
#define LOG_H

#include <iostream>


#if 0
class Log
{
public:
	enum Color{white, red, blue, green};
	void print(std::string);
private:
	std::ostream& outstream = std::cout;
};



Log& operator<<(Log& log, Log::Color col);

Log& operator<<(Log& log, std::string str);
#endif

#endif
