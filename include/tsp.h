#ifndef _TSP_H

#define _TSP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils.h"

#define MAX_LINE_LENGTH 150
#define MAX_CITY_DISTANCE 999999999

#define Item int
#define key(A) (A)
#define diff(A, B) (key(A) - key(B))
#define less(A, B) (key(A) < key(B))
#define swap(A, B) \
	{                \
		Item aux = A;  \
		A = B;         \
		B = aux;       \
	}
#define posToId(POS) (key(POS) + 1)
#define idToPos(ID) (key(ID) - 1)

typedef struct city_struct city;
typedef city *City;
typedef struct tsp_struct TSP;
typedef TSP *TravellingSalesmanProblem;

TravellingSalesmanProblem initTSP();
void readTSPFile(char *fileName, TravellingSalesmanProblem tsp);
void destroyTSP(TravellingSalesmanProblem tsp);
int getDimensionFromTSP(TravellingSalesmanProblem tsp);
City createCity(int id, float x, float y);
City *initCitiesArray(size_t n);
City *getCitiesArrayFromTSP(TravellingSalesmanProblem tsp);
void destroyCitiesArray(City *array, size_t n);
float **initCitiesDistanceMatrix(size_t n);
float **getCitiesDistanceMatrixFromTSP(TravellingSalesmanProblem tsp);
void calculateDistanceBetweenCities(TravellingSalesmanProblem tsp);
void destroyCitiesDistanceMatrix(float **matrix, size_t n);
void printCitiesDistanceMatrix(float **matrix, size_t n);

#endif
