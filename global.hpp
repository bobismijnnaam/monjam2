#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <string>
#include <pthread.h>

extern pthread_mutex_t printMutex;

void cprint(std::string str);

#endif
