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
	clock_t start = clock(), stop = clock();

	if (argc < 2)
	{
		printf("Expected 2 arguments but received %d arguments", argc);
		exit(EXIT_FAILURE);
	}

	start = clock();
	TSP *tsp = initTSP();
	readTSPFile(argv[1], tsp);

	Graph graph = initGraph(getDimensionFromTSP(tsp), 0);
	calculateDistanceBetweenCities(tsp, graph);
	printf("Graph - verticesAmount : %d, edgesAmount: %d\n", getVerticesAmountFromGraph(graph), getEdgesAmountFromGraph(graph));

	Graph mst = buildMST(graph);
	writeMSTFile(getNameFromTSP(tsp), mst);
	printf("MST - verticesAmount : %d, edgesAmount: %d\n", getVerticesAmountFromGraph(mst), getEdgesAmountFromGraph(mst));

	Tour tour = buildTour(graph, mst);
	writeTourFile(getNameFromTSP(tsp), tour);
	printf("Tour - verticesAmount : %d, edgesAmount: %d\n", getVerticesAmountFromTour(tour), getEdgesAmountFromTour(tour));

	printf("\nCusto - Graph: %.2f >= Tour: %.2f >= MST: %.2f\n", getMinCostFromGraph(graph), getMinCostFromTour(tour), getMinCostFromGraph(mst));

	destroyTSP(tsp);
	destroyGraph(graph);
	destroyGraph(mst);
	destroyTour(tour);
	stop = clock();

	printTimeInterval(start, stop, "Full Execution Interval");

	return 0;
}
