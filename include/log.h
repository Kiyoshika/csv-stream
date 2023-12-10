#ifndef CSTREAM_LOG_H
#define CSTREAM_LOG_H

#include <stdio.h>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW	"\033[33m"

#define LOG_OK(message) { \
	printf(GREEN message RESET "\n"); \
}

#define LOG_WARNING(func_name, message) { \
	fprintf(stderr, YELLOW func_name ": WARNING: " message RESET "\n"); \
}

#endif
