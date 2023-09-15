// Travelling Salesman Problem with Minimum Spanning Tree
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../include/tsp.h"
#include "../include/mst.h"
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

	Graph mst = buildMST(graph);

	destroyTSP(tsp);
	destroyGraph(graph);
	destroyGraph(mst);
	stop = clock();

	printTimeInterval(start, stop, "Full Execution Interval");

	return 0;
}
