#ifndef _UTILS_H

#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

void safeFree(void *ptr);
bool wasAllocated(void *pointer);
void printTimeInterval(clock_t start, clock_t stop, char *msg);

#endif
