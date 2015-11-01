#ifndef LOG_H
#define LOG_H

#include <iostream>

#define LOG(param) do{std::cout << this->getTime() << ": " << param << "\n";}while(0)


#endif
