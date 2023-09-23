// Travelling Salesman Problem with Minimum Spanning Tree
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../include/tsp.h"
#include "../include/mst.h"
#include "../include/tour.h"
#include "../include/utils.h"

int main(int argc, char *argv[])
{
	srand(time(NULL));
	clock_t start = clock();

	if (argc < 2)
	{
		printf("Expected 2 arguments but received %d arguments", argc);
		exit(EXIT_FAILURE);
	}

	clock_t tspStart = clock();
	TSP *tsp = initTSP();
	readTSPFile(argv[1], tsp);
	clock_t tspStop = clock();
	printTimeInterval(tspStart, tspStop, "Read TSP Interval");

	char tspName[MAX_LINE_LENGTH] = "";
	strcpy(tspName, getNameFromTSP(tsp));
	printf("%s\n", tspName);

	clock_t graphStart = clock();
	Graph graph = initGraph(getDimensionFromTSP(tsp), 0);
	calculateDistanceBetweenCities(tsp, graph);
	clock_t graphStop = clock();
	printTimeInterval(graphStart, graphStop, "Build Graph Interval");
	printf("Graph - verticesAmount : %d, edgesAmount: %d\n", getVerticesAmountFromGraph(graph), getEdgesAmountFromGraph(graph));

	clock_t mstStart = clock();
	Graph mst = buildMST(graph);
	writeMSTFile(tspName, mst);
	clock_t mstStop = clock();
	printTimeInterval(mstStart, mstStop, "Build MST Interval");
	printf("MST - verticesAmount : %d, edgesAmount: %d\n", getVerticesAmountFromGraph(mst), getEdgesAmountFromGraph(mst));

	clock_t tourStart = clock();
	Tour tour = buildTour(mst);
	writeTourFile(tspName, tour);
	clock_t tourStop = clock();
	printTimeInterval(tourStart, tourStop, "Build Tour Interval");
	printf("Tour - verticesAmount : %d\n", getVerticesAmountFromTour(tour));

	destroyTSP(tsp);
	destroyGraph(graph);
	destroyGraph(mst);
	destroyTour(tour);

	clock_t stop = clock();
	printTimeInterval(start, stop, "Full Execution Interval");

	return 0;
}
