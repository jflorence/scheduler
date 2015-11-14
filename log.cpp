#include "log.h"



template<>
void Log::print<>(Log::Color color)
{

#ifdef __linux__
	if (outstream != std::cout)
		return;
        switch (color)
        {
                case Log::Color::red:
                        outstream << "\033[1;31m";
                        break;
                case Log::Color::green:
                        outstream << "\033[1;32m";
                        break;
                case Log::Color::blue:
                        outstream << "\033[1;34m";
                        break;
                case Log::Color::normal:
                        outstream << "\033[0m";
			break;
		case Log::Color::lightBlue:
			outstream << "\033[34m";
			break;
                default:
                        outstream << "";
                        break;
        }
#endif
}


