#include "global.hpp"
#include <iostream>

pthread_mutex_t printMutex;

void cprint(std::string str) {
	pthread_mutex_lock(&printMutex);

	std::cout << str;

	pthread_mutex_unlock(&printMutex);
}
