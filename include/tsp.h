#ifndef _TSP_H

#define _TSP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./utils.h"

typedef struct city_struct city;
typedef city *City;
typedef struct tsp_struct TSP;
typedef TSP *TravellingSalesmanProblem;

TravellingSalesmanProblem initTSP();
void destroyTSP(TravellingSalesmanProblem tsp);
char *getNameFromTSP(TravellingSalesmanProblem tsp);
int getDimensionFromTSP(TravellingSalesmanProblem tsp);
City createCity(int id, float x, float y);
float getXCoordinateFromCity(City city);
float getYCoordinateFromCity(City city);
City *initCitiesArray(size_t n);
City *getCitiesArrayFromTSP(TravellingSalesmanProblem tsp);
void destroyCitiesArray(City *array, size_t n);
void readTSPFile(char *fileName, TravellingSalesmanProblem tsp);

#endif
