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
	// TODO
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
	Tour newTour = initTour(getVerticesAmountFromGraph(mst));
	Edge *mstEdgesArray = getEdgesArrayFromGraph(mst);
	Edge *generalGraphEdgesArray = getEdgesArrayFromGraph(graph);
	int *visitedVerticesArray = initVisitedVerticesArray(getVerticesAmountFromGraph(mst));

	int allVerticesOccurrencesArray[2 * getEdgesAmountFromGraph(mst)];
	int allVerticesOccurrencesCount = 0;
	for (int i = 0; i < getEdgesAmountFromGraph(mst); i++)
	{
		Edge currentMstEdge = *(mstEdgesArray + i);
		int mstSrcVerticeId = getSourceFromEdge(currentMstEdge);
		int mstDestVerticeId = getDestinationFromEdge(currentMstEdge);

		allVerticesOccurrencesArray[allVerticesOccurrencesCount++] = mstSrcVerticeId;
		allVerticesOccurrencesArray[allVerticesOccurrencesCount++] = mstDestVerticeId;
	}

	int singleVerticesOccurrenceArray[getEdgesAmountFromGraph(mst)];
	int singleVerticesOccurrenceCount = 0;
	for (int i = 0; i < allVerticesOccurrencesCount; i++)
	{
		int verticeId = allVerticesOccurrencesArray[i];

		if (visitedVerticesArray[idToPos(verticeId)] < 1)
		{
			singleVerticesOccurrenceArray[singleVerticesOccurrenceCount++] = verticeId;
			visitedVerticesArray[idToPos(verticeId)] += 1;
		}
	}

	// TODO - melhorar algoritmo para obter custo minimo
	for (int i = 0; i < getEdgesAmountFromGraph(mst); i++)
	{
		int v1 = singleVerticesOccurrenceArray[i];
		int v2 = singleVerticesOccurrenceArray[i + 1];
		Edge minEdge = NULL;
		bool isInverted = false;

		for (int j = 0; j < getEdgesAmountFromGraph(mst); j++)
		{
			Edge currentMstEdge = *(mstEdgesArray + j);
			int mstSrcVerticeId = getSourceFromEdge(currentMstEdge);
			int mstDestVerticeId = getDestinationFromEdge(currentMstEdge);

			if ((v1 == mstSrcVerticeId && v2 == mstDestVerticeId) ||
					(v2 == mstSrcVerticeId && v1 == mstDestVerticeId))
			{
				if (v2 == mstSrcVerticeId && v1 == mstDestVerticeId)
					isInverted = true;

				minEdge = currentMstEdge;
			}
		}
		if (minEdge == NULL)
		{
			for (int k = 0; k < getEdgesAmountFromGraph(graph); k++)
			{
				Edge currentGeneralGraphEdge = *(generalGraphEdgesArray + k);
				int generalGraphSrcVerticeId = getSourceFromEdge(currentGeneralGraphEdge);
				int generalGraphDestVerticeId = getDestinationFromEdge(currentGeneralGraphEdge);

				if ((v1 == generalGraphSrcVerticeId && v2 == generalGraphDestVerticeId) ||
						(v2 == generalGraphSrcVerticeId && v1 == generalGraphDestVerticeId))
				{
					if (v2 == generalGraphSrcVerticeId && v1 == generalGraphDestVerticeId)
						isInverted = true;

					if (minEdge == NULL)
						minEdge = currentGeneralGraphEdge;
					else if (less(getWeightFromEdge(currentGeneralGraphEdge), getWeightFromEdge(minEdge)))
						minEdge = currentGeneralGraphEdge; // never changes if general graph is sorted
				}
			}
		}

		if (minEdge != NULL)
		{
			int src = getSourceFromEdge(minEdge);
			int dest = getDestinationFromEdge(minEdge);
			float w = getWeightFromEdge(minEdge);
			if (isInverted)
				_appendEdgeToTourArray(newTour, createEdge(dest, src, w));
			else
				_appendEdgeToTourArray(newTour, createEdge(src, dest, w));
		}
	}

	Edge *tourEdgesArray = newTour->edgesArray;
	for (int i = 0; i < newTour->edgesAmount; i++)
	{
		Edge currentEdge = *(tourEdgesArray + i);
		printf("%d → %d\n", getSourceFromEdge(currentEdge), getDestinationFromEdge(currentEdge));
		newTour->minCost += getWeightFromEdge(currentEdge);
	}

	safeFree(visitedVerticesArray);
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
