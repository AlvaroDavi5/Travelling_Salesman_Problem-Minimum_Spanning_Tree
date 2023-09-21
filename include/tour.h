#ifndef _TOUR_H

#define _TOUR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "./mst.h"
#include "./utils.h"

typedef struct tour_struct tour;
typedef tour *Tour;

Tour initTour(int verticesAmount);
void destroyTour(Tour tour);
Tour buildTour(Graph graph, Graph mst);
int *initVisitedVerticesArray(int verticesAmount);
int getVerticesAmountFromTour(Tour tour);
int getEdgesAmountFromTour(Tour tour);
float getMinCostFromTour(Tour tour);
void writeTourFile(char *fileSteam, Tour tour);

#endif
