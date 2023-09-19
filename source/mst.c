#include "../include/mst.h"

struct edge_struct
{
	int source, destination;
	float weight;
};

struct graph_struct
{
	int verticesAmount, edgesAmount;
	float minCost;
	Edge *edgesArray;
	int lastSettedEdge;
};

struct subset_struct
{
	int parent;
	int rank;
};

Graph initGraph(int verticesAmount, int edgesAmount)
{
	Graph newGraph = (graph *)malloc(sizeof(graph));

	if (!wasAllocated(newGraph))
		return NULL;

	newGraph->verticesAmount = verticesAmount;
	if (edgesAmount == 0)
		edgesAmount = (verticesAmount * (verticesAmount - 1)) / 2; // E = (V * (V - 1)) / 2
	newGraph->edgesAmount = edgesAmount;
	newGraph->edgesArray = initEdgesArray(edgesAmount);
	newGraph->lastSettedEdge = -1;
	newGraph->minCost = 0;

	return newGraph;
}

void writeMSTFile(char *fileName, Graph mst)
{
}

void destroyGraph(Graph graph)
{
	destroyEdgesArray(graph->edgesArray, graph->edgesAmount);
	safeFree(graph);
}

Subset *initSubSets(int verticesAmount)
{
	Subset *newSubSets = (Subset *)malloc(verticesAmount * sizeof(Subset));

	for (int i = 0; i < verticesAmount; i++)
	{
		newSubSets[i].parent = i;
		newSubSets[i].rank = 0;
	}

	return newSubSets;
}

void destroySubSets(Subset *subsets)
{
	safeFree(subsets);
}

int findSet(Subset *subsets, int component)
{
	if (subsets[component].parent != component)
		subsets[component].parent = findSet(subsets, subsets[component].parent);

	return subsets[component].parent;
}

void unionSet(Subset *subsets, int src, int dest)
{
	int srcSet = findSet(subsets, src);
	int destSet = findSet(subsets, dest);

	if (subsets[srcSet].rank < subsets[destSet].rank)
		subsets[srcSet].parent = destSet;
	else if (subsets[srcSet].rank > subsets[destSet].rank)
		subsets[destSet].parent = srcSet;
	else
	{
		subsets[destSet].parent = srcSet;
		subsets[srcSet].rank++;
	}
}

int _compareEdgesWeight(const void *a, const void *b)
{
	const Edge edgeA = *(const Edge *)a;
	const Edge edgeB = *(const Edge *)b;

	if (edgeA->weight < edgeB->weight)
		return -1;
	if (edgeA->weight > edgeB->weight)
		return 1;
	return 0;
}

Graph buildMST(Graph graph) // Kruskal Algorithm
{
	// sorting all edges in increasing order of their edge weights
	qsort(graph->edgesArray, graph->edgesAmount, sizeof(Edge), _compareEdgesWeight);

	// creating vertices subsets
	Subset *subSets = initSubSets(graph->verticesAmount);

	// initialize MST
	Graph mst = initGraph(graph->verticesAmount, graph->verticesAmount - 1); // E = (V - 1)
	int mstEdges = 0;
	float minCost = 0.0;

	// iterate through sorted edges
	for (int i = 0; i < graph->edgesAmount; i++)
	{
		Edge currentEdge = graph->edgesArray[i];
		int sourceSet = findSet(subSets, idToPos(currentEdge->source));
		int destinationSet = findSet(subSets, idToPos(currentEdge->destination));
		float edgeWeight = currentEdge->weight;

		if (sourceSet != destinationSet) // check if the edges sets are diferent to avoid cycle
		{
			// add it to the MST
			mst->edgesArray[mstEdges++] = createEdge(currentEdge->source, currentEdge->destination, currentEdge->weight);
			minCost += edgeWeight;
			// unify subsets
			unionSet(subSets, sourceSet, destinationSet);
		}
	}

	destroySubSets(subSets);
	mst->minCost = minCost;

	return mst;
}

int getVerticesAmountFromGraph(Graph graph)
{
	return graph->verticesAmount;
}

int getEdgesAmountFromGraph(Graph graph)
{
	return graph->edgesAmount;
}

float getMinCostFromGraph(Graph graph)
{
	return graph->minCost;
}

Edge createEdge(int src, int dest, float w)
{
	Edge newEdge = (edge *)malloc(sizeof(edge));

	if (!wasAllocated(newEdge))
		return NULL;

	newEdge->source = src;
	newEdge->destination = dest;
	newEdge->weight = w;

	return newEdge;
}

int getSourceFromEdge(Edge edge)
{
	return edge->source;
}

int getDestinationFromEdge(Edge edge)
{
	return edge->destination;
}

float getWeightFromEdge(Edge edge)
{
	return edge->weight;
}

Edge *initEdgesArray(int edgesAmount)
{
	Edge *edgesArray = (Edge *)malloc(edgesAmount * sizeof(Edge));

	if (!wasAllocated(edgesArray))
		return NULL;

	return edgesArray;
}

void _appendEdgeToGraphArray(Graph graph, Edge edge)
{
	if (!wasAllocated(graph->edgesArray) || graph->lastSettedEdge == (graph->edgesAmount - 1))
		return;

	int pos = graph->lastSettedEdge + 1;
	graph->edgesArray[pos] = edge;
	graph->lastSettedEdge = pos;
}

Edge *getEdgesArrayFromGraph(Graph graph)
{
	return graph->edgesArray;
}

void destroyEdgesArray(Edge *array, size_t n)
{
	if (wasAllocated(array))
	{
		for (size_t i = 0; i < n; i++)
		{
			safeFree(*(array + i));
		}

		safeFree(array);
	}
}

void calculateDistanceBetweenCities(TravellingSalesmanProblem tsp, Graph graph)
{
	int tspDimension = getDimensionFromTSP(tsp);
	City *citiesArray = getCitiesArrayFromTSP(tsp);

	if (!wasAllocated(citiesArray) || !wasAllocated(graph->edgesArray))
		return;

	for (int i = 0; i < tspDimension; i++)
	{
		for (int j = 0; j < tspDimension; j++)
		{
			if (j >= i) // ignore pivots (distance between a city and itself) and transposed values ​(repeated distances)
				continue;
			else
			{
				City rowCity = *(citiesArray + i);
				City columnCity = *(citiesArray + j);

				float xDiff = diff(getXCoordinateFromCity(rowCity), getXCoordinateFromCity(columnCity));
				float yDiff = diff(getYCoordinateFromCity(rowCity), getYCoordinateFromCity(columnCity));
				// H^2 = OC^2 + AC^2
				float distance = (float)sqrt(pow(xDiff, 2) + pow(yDiff, 2));

				_appendEdgeToGraphArray(graph, createEdge(posToId(i), posToId(j), distance));
				graph->minCost += distance;
			}
		}
	}
}
