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
	int edgesAmount = verticesAmount; // E = V
	newTour->edgesAmount = edgesAmount;
	newTour->edgesArray = initEdgesArray(edgesAmount);
	newTour->lastSettedEdge = -1;
	newTour->minCost = 0;

	return newTour;
}

void destroyTour(Tour tour)
{
	destroyEdgesArray(tour->edgesArray, tour->edgesAmount);
	safeFree(tour);
}

void _appendEdgeToTourArray(Tour tour, Edge edge)
{
	if (!wasAllocated(tour->edgesArray) || tour->lastSettedEdge == (tour->edgesAmount - 1))
		return;

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
		bool isInverted = addedVerticesArray[idToPos(destVerticeId)] > addedVerticesArray[idToPos(srcVerticeId)];

		if (addedVerticesArray[idToPos(srcVerticeId)] < 2 &&
				addedVerticesArray[idToPos(destVerticeId)] < 2)
		{
			float w = getWeightFromEdge(currentEdge);

			if (isInverted)
				_appendEdgeToTourArray(newTour, createEdge(destVerticeId, srcVerticeId, w));
			else
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
		bool isInverted = addedVerticesArray[idToPos(destVerticeId)] > addedVerticesArray[idToPos(srcVerticeId)];

		if (addedVerticesArray[idToPos(srcVerticeId)] < 2 &&
				addedVerticesArray[idToPos(destVerticeId)] < 2)
		{
			float w = getWeightFromEdge(currentEdge);

			if (isInverted)
				_appendEdgeToTourArray(newTour, createEdge(destVerticeId, srcVerticeId, w));
			else
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

void writeTourFile(char *fileSteam, Tour tour)
{
	char fileName[MAX_LINE_LENGTH] = "./output/";
	strcat(fileName, fileSteam);
	strcat(fileName, ".tour");

	FILE *file = fopen(fileName, "a");

	fprintf(file, "NAME: %s\n", fileSteam);
	fprintf(file, "TYPE: TOUR\n");
	fprintf(file, "DIMENSION: %d\n", getVerticesAmountFromTour(tour));

	fprintf(file, "TOUR_SECTION\n");
	Edge *edgesArray = tour->edgesArray;
	for (int i = 0; i < getEdgesAmountFromTour(tour); i++)
	{
		Edge currentEdge = *(edgesArray + i);
		fprintf(file, "%d\n", getDestinationFromEdge(currentEdge));
	}
	fprintf(file, "EOF\n");

	fclose(file);
}
