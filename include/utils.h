#ifndef _UTILS_H

#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 150

#define posToId(POS) (POS + 1)
#define idToPos(ID) (ID - 1)
#define diff(A, B) (A - B)
#define less(A, B) (A < B)

void safeFree(void *ptr);
bool wasAllocated(void *pointer);
void printTimeInterval(clock_t start, clock_t stop, char *msg);

#endif
