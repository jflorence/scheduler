#include "log.h"



void Log::print(std::string str)
{
	outstream << str;
}


Log& operator<<(Log& log, std::string str)
{
	log.print(str);
	return log;
}

Log& operator<<(Log& log, Log::Color col)
{
	switch (col)
	{
	case Log::Color::white:
		return operator<<(log, "\033[0m");
		break;
	case Log::Color::blue:
		return operator<<(log, "\033[1;34m");
		break;
	case Log::Color::red:
		return operator<<(log, "\033[1;31m");
		break;
	case Log::Color::green:
		return operator<<(log, "\033[1;32m");
		break;
	default:
		break;
	}
	return operator<<(log, "");;
}




