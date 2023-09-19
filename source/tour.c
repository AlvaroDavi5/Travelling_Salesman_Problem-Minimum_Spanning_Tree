#include "../include/tour.h"

struct tour_struct
{
	int verticesAmount, edgesAmount;
	float minCost;
	Edge *edgesArray;
	int lastSettedEdge;
	bool *visitedVerticesArray;
	int visitedVerticesCount;
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
	newTour->visitedVerticesArray = initVisitedVerticesArray(verticesAmount);
	newTour->visitedVerticesCount = 0;
	newTour->minCost = 0;

	return newTour;
}

void writeTourFile(char *fileName, Tour tour)
{
}

void destroyTour(Tour tour)
{
	destroyEdgesArray(tour->edgesArray, tour->edgesAmount);
	safeFree(tour->visitedVerticesArray);
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

int _compareEdgesSrc(const void *a, const void *b)
{
	const Edge edgeA = *(const Edge *)a;
	const Edge edgeB = *(const Edge *)b;

	if (getSourceFromEdge(edgeA) < getSourceFromEdge(edgeB))
		return -1;
	if (getSourceFromEdge(edgeA) > getSourceFromEdge(edgeB))
		return 1;
	return 0;
}

int _compareEdgesDest(const void *a, const void *b)
{
	const Edge edgeA = *(const Edge *)a;
	const Edge edgeB = *(const Edge *)b;

	if (getDestinationFromEdge(edgeA) != getSourceFromEdge(edgeB))
		return -1;
	if (getDestinationFromEdge(edgeA) == getSourceFromEdge(edgeB))
		return 1;
	return 0;
}

Tour buildTour(Graph graph, Graph mst)
{
	Tour newTour = initTour(getVerticesAmountFromGraph(mst));
	// TODO: tentar com recursao
	Edge *mstEdgesArray = getEdgesArrayFromGraph(mst);
	Edge *generalGraphEdgesArray = getEdgesArrayFromGraph(graph);

	for (int i = 0; i < getEdgesAmountFromGraph(mst); i++)
	{
		Edge currentMSTEdge = *(mstEdgesArray + i);
		int mstSrcVerticeId = getSourceFromEdge(currentMSTEdge);
		int mstDestVerticeId = getDestinationFromEdge(currentMSTEdge);

		newTour->visitedVerticesArray[idToPos(mstSrcVerticeId)] = true;
		if (newTour->visitedVerticesArray[idToPos(mstDestVerticeId)] == false)
		{
			_appendEdgeToTourArray(newTour, createEdge(getSourceFromEdge(currentMSTEdge),
																								 getDestinationFromEdge(currentMSTEdge),
																								 getWeightFromEdge(currentMSTEdge)));
			newTour->visitedVerticesArray[idToPos(mstDestVerticeId)] = true;
			newTour->visitedVerticesCount += 1;
		}
		else
		{
			Edge minGeneralGraphEdge = NULL;

			for (int j = 0; j < getEdgesAmountFromGraph(graph); j++)
			{
				Edge currentGeneralGraphEdge = *(generalGraphEdgesArray + j);
				int generalGraphSrcVerticeId = getSourceFromEdge(currentGeneralGraphEdge);
				int generalGraphDestVerticeId = getDestinationFromEdge(currentGeneralGraphEdge);

				if ((mstSrcVerticeId == generalGraphSrcVerticeId || mstSrcVerticeId == generalGraphDestVerticeId) &&
						(mstDestVerticeId != generalGraphSrcVerticeId && mstDestVerticeId != generalGraphDestVerticeId))
				{
					if (minGeneralGraphEdge == NULL)
						minGeneralGraphEdge = currentGeneralGraphEdge;
					else if (less(getWeightFromEdge(currentGeneralGraphEdge), getWeightFromEdge(minGeneralGraphEdge))) // never changes if general graph is sorted
						minGeneralGraphEdge = currentGeneralGraphEdge;
				}
			}

			if (minGeneralGraphEdge != NULL)
			{
				int minEdgeSrcVerticeId = getSourceFromEdge(minGeneralGraphEdge);
				int minEdgeDestVerticeId = getDestinationFromEdge(minGeneralGraphEdge);
				int minEdgeWeight = getWeightFromEdge(minGeneralGraphEdge);

				if (mstSrcVerticeId == minEdgeSrcVerticeId)
				{
					_appendEdgeToTourArray(newTour, createEdge(minEdgeSrcVerticeId, minEdgeDestVerticeId, minEdgeWeight));
					newTour->visitedVerticesArray[idToPos(minEdgeDestVerticeId)] = true;
				}
				else
				{
					_appendEdgeToTourArray(newTour, createEdge(minEdgeDestVerticeId, minEdgeSrcVerticeId, minEdgeWeight));
					newTour->visitedVerticesArray[idToPos(minEdgeSrcVerticeId)] = true;
				}
				newTour->visitedVerticesCount += 1;
			}
		}
	}

	qsort(newTour->edgesArray, newTour->edgesAmount, sizeof(Edge), _compareEdgesSrc);
	qsort(newTour->edgesArray, newTour->edgesAmount, sizeof(Edge), _compareEdgesDest);

	int firstSrcVerticeId = getSourceFromEdge(newTour->edgesArray[0]);
	int lastSrcVerticeId = getSourceFromEdge(newTour->edgesArray[newTour->edgesAmount - 1]);
	if (firstSrcVerticeId != lastSrcVerticeId)
	{
		Edge minGeneralGraphEdge = NULL;

		for (int i = 0; i < getEdgesAmountFromGraph(graph); i++)
		{
			Edge currentGeneralGraphEdge = *(generalGraphEdgesArray + i);
			int generalGraphSrcVerticeId = getSourceFromEdge(currentGeneralGraphEdge);
			int generalGraphDestVerticeId = getDestinationFromEdge(currentGeneralGraphEdge);

			if ((generalGraphSrcVerticeId == lastSrcVerticeId && generalGraphDestVerticeId == firstSrcVerticeId) ||
					(generalGraphDestVerticeId == lastSrcVerticeId && generalGraphSrcVerticeId == firstSrcVerticeId))
			{
				if (minGeneralGraphEdge == NULL)
					minGeneralGraphEdge = currentGeneralGraphEdge;
				else if (less(getWeightFromEdge(currentGeneralGraphEdge), getWeightFromEdge(minGeneralGraphEdge))) // never changes if general graph is sorted
					minGeneralGraphEdge = currentGeneralGraphEdge;
			}
		}

		if (minGeneralGraphEdge != NULL)
		{
			int minEdgeSrcVerticeId = getSourceFromEdge(minGeneralGraphEdge);
			int minEdgeDestVerticeId = getDestinationFromEdge(minGeneralGraphEdge);
			int minEdgeWeight = getWeightFromEdge(minGeneralGraphEdge);

			if (lastSrcVerticeId == minEdgeSrcVerticeId)
			{
				_appendEdgeToTourArray(newTour, createEdge(minEdgeSrcVerticeId, minEdgeDestVerticeId, minEdgeWeight));
				newTour->visitedVerticesArray[idToPos(minEdgeDestVerticeId)] = true;
			}
			else
			{
				_appendEdgeToTourArray(newTour, createEdge(minEdgeDestVerticeId, minEdgeSrcVerticeId, minEdgeWeight));
				newTour->visitedVerticesArray[idToPos(minEdgeSrcVerticeId)] = true;
			}
			newTour->visitedVerticesCount += 1;
		}
	}

	Edge *tourEdgesArray = newTour->edgesArray;
	for (int k = 0; k < newTour->edgesAmount; k++)
	{
		Edge currentEdge = *(tourEdgesArray + k);
		printf("%d → %d\n", getSourceFromEdge(currentEdge), getDestinationFromEdge(currentEdge));
		newTour->minCost += getWeightFromEdge(currentEdge);
	}

	printf("\n\nTour - verticesAmount : %d, edgesAmount: %d, visitedVerticesCount: %d\n\n", newTour->verticesAmount, newTour->edgesAmount, newTour->visitedVerticesCount);

	return newTour;
}

bool *initVisitedVerticesArray(int verticesAmount)
{
	bool *newVisitedVerticesArray = (bool *)malloc(verticesAmount * sizeof(bool));

	if (!wasAllocated(newVisitedVerticesArray))
		return NULL;

	for (int i = 0; i < verticesAmount; i++)
	{
		*(newVisitedVerticesArray + i) = false;
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
