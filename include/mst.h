#ifndef _MST_H

#define _MST_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./tsp.h"
#include "./utils.h"

#define MAX_MST_COST 999999999

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
Edge createEdge(int src, int dest, float w);
Edge *initEdgesArray(int edgesAmount);
void appendEdgeToArray(Graph graph, Edge edge);
Edge *getEdgesArrayFromGraph(Graph graph);
void destroyEdgesArray(Edge *array, size_t n);
void calculateDistanceBetweenCities(TravellingSalesmanProblem tsp, Graph graph);
void quickSort(Item *array, size_t begin, size_t end);

#endif
