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

// O(N)
int findSet(Subset *subsets, int component)
{
	if (subsets[component].parent != component)
		subsets[component].parent = findSet(subsets, subsets[component].parent); // recursion is like a loop/iteration

	return subsets[component].parent;
}

// 2O(N) == O(N)
void unionSet(Subset *subsets, int src, int dest)
{
	int srcSet = findSet(subsets, src); // O(N)
	int destSet = findSet(subsets, dest); // O(N)

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

// O(N * lg(N)) + O(N) * (2O(N) + O(N)) == O(N * lg(N)) + O(N^2)
Graph buildMST(Graph graph) // Kruskal Algorithm
{
	// sorting all edges in increasing order of their edge weights
	qsort(graph->edgesArray, graph->edgesAmount, sizeof(Edge), _compareEdgesWeight); // O(N * lg(N))

	// creating vertices subsets
	Subset *subSets = initSubSets(graph->verticesAmount);

	// initialize MST
	Graph mst = initGraph(graph->verticesAmount, graph->verticesAmount - 1); // E = (V - 1)
	int mstEdges = 0;
	float minCost = 0.0;

	// iterate through sorted edges
	for (int i = 0; i < graph->edgesAmount; i++) // O(N)
	{
		Edge currentEdge = graph->edgesArray[i];
		int sourceSet = findSet(subSets, idToPos(currentEdge->source)); // O(N)
		int destinationSet = findSet(subSets, idToPos(currentEdge->destination)); // O(N)
		float edgeWeight = currentEdge->weight;

		if (sourceSet != destinationSet) // check if the edges sets are diferent to avoid cycle
		{
			// add it to the MST
			mst->edgesArray[mstEdges++] = createEdge(currentEdge->source, currentEdge->destination, currentEdge->weight);
			minCost += edgeWeight;
			// unify subsets
			unionSet(subSets, sourceSet, destinationSet); // O(N)
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

// O(N)
bool isEdgeInGraph(Edge *edgesArray, int edgesAmount, int v1, int v2)
{
	for (int i = 0; i < edgesAmount; i++)
	{
		Edge currentEdge = edgesArray[i];
		int srcVertexId = currentEdge->source;
		int destVertexId = currentEdge->destination;

		if ((srcVertexId == v1 && destVertexId == v2) ||
				(srcVertexId == v2 && destVertexId == v1))
			return true;
	}

	return false;
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

// O(N^2)
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

// O(N)
void writeMSTFile(char *fileSteam, Graph mst)
{
	char fileName[MAX_LINE_LENGTH] = "./output/";
	strcat(fileName, fileSteam);
	strcat(fileName, ".mst");

	FILE *file = fopen(fileName, "w");

	fprintf(file, "NAME: %s\n", fileSteam);
	fprintf(file, "TYPE: MST\n");
	fprintf(file, "DIMENSION: %d\n", getVerticesAmountFromGraph(mst));

	fprintf(file, "MST_SECTION\n");
	Edge *edgesArray = getEdgesArrayFromGraph(mst);
	for (int i = 0; i < getEdgesAmountFromGraph(mst); i++)
	{
		Edge currentEdge = *(edgesArray + i);
		fprintf(file, "%d %d\n", getDestinationFromEdge(currentEdge), getSourceFromEdge(currentEdge));
	}
	fprintf(file, "EOF\n");

	fclose(file);
}
