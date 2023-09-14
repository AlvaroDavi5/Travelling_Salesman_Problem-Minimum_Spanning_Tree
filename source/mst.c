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
	newGraph->minCost = MAX_TOUR_COST;

	return newGraph;
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

Graph buildMST(Graph graph) // Kruskal Algorithm
{
	float minCost = 0.0;

	// sorting all edges in increasing order of their edge weights
	quickSort(graph->edgesArray, 0, (graph->edgesAmount - 1));

	// creating vertices subsets
	Subset *subSets = initSubSets(graph->verticesAmount);

	// initialize MST
	Graph MST = initGraph(graph->verticesAmount, graph->verticesAmount - 1); // E = (V - 1)
	int mstEdges = 0;

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
			MST->edgesArray[mstEdges++] = createEdge(currentEdge->source, currentEdge->destination, currentEdge->weight);
			minCost += edgeWeight;
			// unify subsets
			unionSet(subSets, sourceSet, destinationSet);
		}
	}

	destroySubSets(subSets);
	MST->minCost = minCost;

	return MST;
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

Edge *initEdgesArray(int edgesAmount)
{
	Edge *edgesArray = (Edge *)malloc(edgesAmount * sizeof(Edge));

	if (!wasAllocated(edgesArray))
		return NULL;

	return edgesArray;
}

void appendEdgeToArray(Graph graph, Edge edge)
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

void createEdgesByDistanceMatrix(Graph graph, float **distanceMatrix, size_t n)
{
	if (!wasAllocated(graph->edgesArray))
		return;

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			if (j >= i) // ignore pivots and transposed values
				continue;
			else
			{
				float weight = *(*(distanceMatrix + i) + j);
				appendEdgeToArray(graph, createEdge(posToId(i), posToId(j), weight));
			}
		}
	}
}

size_t _partition(Item *array, size_t begin, size_t end)
{
	size_t pivotIndex = begin;
	Item pivotElement = array[end];

	for (size_t i = begin; i < end; i++)
	{
		if (array[i]->weight <= pivotElement->weight)
		{
			swap(array[i], array[pivotIndex]);
			pivotIndex++;
		}
	}

	swap(array[pivotIndex], array[end]);

	return pivotIndex;
}

size_t _randomPartition(Item *array, size_t begin, size_t end)
{
	size_t pivotIndex = begin + (rand() % (end - begin + 1));

	swap(array[pivotIndex], array[end]);
	return _partition(array, begin, end);
}

void quickSort(Item *array, size_t begin, size_t end)
{
	if (begin < end)
	{
		size_t partitionIndex = _randomPartition(array, begin, end);
		if (partitionIndex > 0)
			quickSort(array, begin, partitionIndex - 1);
		quickSort(array, partitionIndex + 1, end);
	}
}
