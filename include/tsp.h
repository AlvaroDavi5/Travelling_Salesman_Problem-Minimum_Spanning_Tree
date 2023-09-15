#ifndef _TSP_H

#define _TSP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "./utils.h"

#define MAX_LINE_LENGTH 150
#define MAX_CITY_DISTANCE 999999999

typedef struct city_struct city;
typedef city *City;
typedef struct tsp_struct TSP;
typedef TSP *TravellingSalesmanProblem;

TravellingSalesmanProblem initTSP();
void readTSPFile(char *fileName, TravellingSalesmanProblem tsp);
void destroyTSP(TravellingSalesmanProblem tsp);
int getDimensionFromTSP(TravellingSalesmanProblem tsp);
City createCity(int id, float x, float y);
int getIDFromCity(City city);
float getXCoordinateFromCity(City city);
float getYCoordinateFromCity(City city);
City *initCitiesArray(size_t n);
City *getCitiesArrayFromTSP(TravellingSalesmanProblem tsp);
void destroyCitiesArray(City *array, size_t n);

#endif
