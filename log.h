#ifndef LOG_H
#define LOG_H

#include <iostream>


class Log
{
public:
	enum Color{normal, red, blue, green, lightBlue};
	template<typename T> void print(T);
private:
	std::ostream& outstream = std::cout;
};





/*template<>
void Log::print<>(Log::Color color);
*/


template<typename T>
void Log::print(T data)
{
        outstream << data;
}




template<typename T>
Log& operator<<(Log& log, T data)
{
	log.print(data);
	return log;
}


#endif

