#ifndef LOG_H
#define LOG_H

#include <iostream>

#define log(param1, param2) do{std::cout << (param1)->getTime() << ": " << param2 << "\n";}while(0)


#endif
