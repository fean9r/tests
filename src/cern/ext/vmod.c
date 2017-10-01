#include "vmod.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static const double memory[8] = {0.1,9.9,20.0,4.4,5.5,6.6,7.7,8.8};

double readHardware(uint16_t address)
{
	time_t t;
	srand((unsigned) time(&t));
	unsigned int microseconds = rand() % 10 * 2;
	usleep(microseconds);
	return memory[address % 8] + microseconds;
}
