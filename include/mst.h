#ifndef _MST_H

#define _MST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "./tsp.h"
#include "./utils.h"

typedef struct edge_struct edge;
typedef edge *Edge;
typedef struct graph_struct graph;
typedef graph *Graph;
typedef struct subset_struct Subset;

#define Item Edge
#define swap(A, B) \
	{                \
		Item aux = A;  \
		A = B;         \
		B = aux;       \
	}

Graph initGraph(int verticesAmount, int edgesAmount);
void destroyGraph(Graph graph);
Graph buildMST(Graph graph);
int getVerticesAmountFromGraph(Graph graph);
int getEdgesAmountFromGraph(Graph graph);
float getMinCostFromGraph(Graph graph);
Edge createEdge(int src, int dest, float w);
int getSourceFromEdge(Edge edge);
int getDestinationFromEdge(Edge edge);
float getWeightFromEdge(Edge edge);
Edge *initEdgesArray(int edgesAmount);
Edge *getEdgesArrayFromGraph(Graph graph);
bool isEdgeInGraph(Edge *edgesArray, int edgesAmount, int v1, int v2);
void destroyEdgesArray(Edge *array, size_t n);
void calculateDistanceBetweenCities(TravellingSalesmanProblem tsp, Graph graph);
void writeMSTFile(char *fileSteam, Graph mst);

#endif
