#include "../include/tour.h"

struct tour_struct
{
	int verticesAmount;
	int *tourArray;
	int tourIndex;
};

Tour initTour(int verticesAmount)
{
	Tour newTour = (tour *)malloc(sizeof(tour));

	if (!wasAllocated(newTour))
		return NULL;

	newTour->verticesAmount = verticesAmount;
	newTour->tourArray = initTourArray(verticesAmount);
	newTour->tourIndex = 0;

	return newTour;
}

void destroyTour(Tour tour)
{
	safeFree(tour->tourArray);
	safeFree(tour);
}

void depthFirstSearch(Tour tour, bool *visitedVerticesArray, Edge *mstEdgesArray, int mstVerticesAmount, int mstEdgesAmount, int vertexIndex)
{
	int vertexId = posToId(vertexIndex);
	tour->tourArray[tour->tourIndex++] = vertexId;
	visitedVerticesArray[vertexIndex] = true;

	for (int i = 0; i < mstVerticesAmount; i++)
	{
		if (!visitedVerticesArray[i] && isEdgeInGraph(mstEdgesArray, mstEdgesAmount, vertexId, posToId(i)))
			depthFirstSearch(tour, visitedVerticesArray, mstEdgesArray, mstVerticesAmount, mstEdgesAmount, i);
	}
}

Tour buildTour(Graph mst)
{
	const int mstVerticesAmount = getVerticesAmountFromGraph(mst);
	Tour newTour = initTour(mstVerticesAmount);

	Edge *mstEdgesArray = getEdgesArrayFromGraph(mst);
	const int mstEdgesAmount = getEdgesAmountFromGraph(mst);
	bool visitedVerticesArray[mstVerticesAmount];
	for (int i = 0; i < mstVerticesAmount; i++)
		visitedVerticesArray[i] = false;

	depthFirstSearch(newTour, visitedVerticesArray, mstEdgesArray, mstVerticesAmount, mstEdgesAmount, 0);

	return newTour;
}

int *initTourArray(int verticesAmount)
{
	int *newTourArray = (int *)malloc(verticesAmount * sizeof(int));

	if (!wasAllocated(newTourArray))
		return NULL;

	for (int i = 0; i < verticesAmount; i++)
	{
		*(newTourArray + i) = 0;
	}

	return newTourArray;
}

int getVerticesAmountFromTour(Tour tour)
{
	return tour->verticesAmount;
}

void writeTourFile(char *fileSteam, Tour tour)
{
	char fileName[MAX_LINE_LENGTH] = "./output/";
	strcat(fileName, fileSteam);
	strcat(fileName, ".tour");

	FILE *file = fopen(fileName, "w");

	int tourVerticesAmount = getVerticesAmountFromTour(tour);
	fprintf(file, "NAME: %s\n", fileSteam);
	fprintf(file, "TYPE: TOUR\n");
	fprintf(file, "DIMENSION: %d\n", tourVerticesAmount);

	fprintf(file, "TOUR_SECTION\n");
	int *tourArray = tour->tourArray;
	for (int i = 0; i < tourVerticesAmount; i++)
	{
		int currentVertice = *(tourArray + i);
		fprintf(file, "%d\n", currentVertice);
	}
	fprintf(file, "EOF\n");

	fclose(file);
}
