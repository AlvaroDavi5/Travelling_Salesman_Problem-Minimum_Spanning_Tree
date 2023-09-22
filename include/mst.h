#ifndef _MST_H

#define _MST_H

#include <stdio.h>
#include <stdlib.h>
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
Subset *initSubSets(int verticesAmount);
void destroySubSets(Subset *subsets);
int findSet(Subset *subsets, int component);
void unionSet(Subset *subsets, int src, int dest);
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
void destroyEdgesArray(Edge *array, size_t n);
void calculateDistanceBetweenCities(TravellingSalesmanProblem tsp, Graph graph);
void writeMSTFile(char *fileSteam, Graph mst);

#endif
