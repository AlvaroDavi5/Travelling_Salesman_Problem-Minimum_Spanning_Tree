#include "../include/tour.h"

struct tour_struct
{
	int verticesAmount, edgesAmount;
	float minCost;
	Edge *edgesArray;
	int lastSettedEdge;
};

Tour initTour(int verticesAmount)
{
	Tour newTour = (tour *)malloc(sizeof(tour));

	if (!wasAllocated(newTour))
		return NULL;

	newTour->verticesAmount = verticesAmount;
	newTour->edgesAmount = 0;
	newTour->edgesArray = NULL;
	newTour->lastSettedEdge = -1;
	newTour->minCost = 0;

	return newTour;
}

void writeTourFile(char *fileName, Tour tour)
{
}

void destroyTour(Tour tour)
{
	destroyEdgesArray(tour->edgesArray, tour->edgesAmount);
	safeFree(tour);
}

void _appendEdgeToTourArray(Tour tour, Edge edge)
{
	if (!wasAllocated(tour->edgesArray) && tour->edgesAmount == 0)
	{
		tour->edgesArray = (Edge *)malloc(1 * sizeof(Edge));
	}
	else if (!wasAllocated(tour->edgesArray))
		return;

	tour->edgesAmount += 1;
	tour->edgesArray = (Edge *)realloc(tour->edgesArray, tour->edgesAmount * sizeof(Edge));

	int pos = tour->lastSettedEdge + 1;
	tour->edgesArray[pos] = edge;
	tour->lastSettedEdge = pos;
}

Tour buildTour(Graph graph, Graph mst)
{
	const int mstVerticesAmount = getVerticesAmountFromGraph(mst);
	Tour newTour = initTour(mstVerticesAmount);
	int *addedVerticesArray = initVisitedVerticesArray(mstVerticesAmount);

	// add edges from MST (sorted by weight)
	Edge *mstEdgesArray = getEdgesArrayFromGraph(mst);
	for (int i = 0; i < getEdgesAmountFromGraph(mst); i++)
	{
		Edge currentEdge = *(mstEdgesArray + i);
		int srcVerticeId = getSourceFromEdge(currentEdge);
		int destVerticeId = getDestinationFromEdge(currentEdge);

		if (addedVerticesArray[idToPos(srcVerticeId)] < 2 &&
				addedVerticesArray[idToPos(destVerticeId)] < 2)
		{
			float w = getWeightFromEdge(currentEdge);

			_appendEdgeToTourArray(newTour, createEdge(srcVerticeId, destVerticeId, w));
			newTour->minCost += w;
			addedVerticesArray[idToPos(srcVerticeId)] += 1;
			addedVerticesArray[idToPos(destVerticeId)] += 1;
		}
	}

	// add edges from General Graph (sorted by weight)
	Edge *generalGraphEdgesArray = getEdgesArrayFromGraph(graph);
	for (int i = 0; i < getEdgesAmountFromGraph(graph); i++)
	{
		Edge currentEdge = *(generalGraphEdgesArray + i);
		int srcVerticeId = getSourceFromEdge(currentEdge);
		int destVerticeId = getDestinationFromEdge(currentEdge);

		if (addedVerticesArray[idToPos(srcVerticeId)] < 2 &&
				addedVerticesArray[idToPos(destVerticeId)] < 2)
		{
			float w = getWeightFromEdge(currentEdge);

			_appendEdgeToTourArray(newTour, createEdge(srcVerticeId, destVerticeId, w));
			newTour->minCost += w;

			addedVerticesArray[idToPos(srcVerticeId)] += 1;
			addedVerticesArray[idToPos(destVerticeId)] += 1;
		}
	}

	safeFree(addedVerticesArray);
	return newTour;
}

int *initVisitedVerticesArray(int verticesAmount)
{
	int *newVisitedVerticesArray = (int *)malloc(verticesAmount * sizeof(int));

	if (!wasAllocated(newVisitedVerticesArray))
		return NULL;

	for (int i = 0; i < verticesAmount; i++)
	{
		*(newVisitedVerticesArray + i) = 0;
	}

	return newVisitedVerticesArray;
}

int getVerticesAmountFromTour(Tour tour)
{
	return tour->verticesAmount;
}

int getEdgesAmountFromTour(Tour tour)
{
	return tour->edgesAmount;
}

float getMinCostFromTour(Tour tour)
{
	return tour->minCost;
}
