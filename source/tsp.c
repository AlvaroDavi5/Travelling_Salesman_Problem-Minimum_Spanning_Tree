#include "../include/tsp.h"

struct city_struct
{
	int id;
	float x, y;
};

struct tsp_struct
{
	char *name;
	int dimension;
	City *citiesArray;
};

TravellingSalesmanProblem initTSP()
{
	TravellingSalesmanProblem tsp = (TSP *)malloc(sizeof(TSP));

	if (!wasAllocated(tsp))
		return NULL;

	tsp->name = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));
	tsp->dimension = 0;
	tsp->citiesArray = NULL;

	return tsp;
}

void destroyTSP(TravellingSalesmanProblem tsp)
{
	safeFree(tsp->name);
	destroyCitiesArray(tsp->citiesArray, tsp->dimension);

	safeFree(tsp);
}

char *getNameFromTSP(TravellingSalesmanProblem tsp)
{
	return tsp->name;
}

int getDimensionFromTSP(TravellingSalesmanProblem tsp)
{
	return tsp->dimension;
}

City createCity(int id, float x, float y)
{
	City newCity = (city *)malloc(sizeof(city));

	if (!wasAllocated(newCity))
		return NULL;

	newCity->id = id;
	newCity->x = x;
	newCity->y = y;

	return newCity;
}

int getIDFromCity(City city)
{
	return city->id;
}

float getXCoordinateFromCity(City city)
{
	return city->x;
}

float getYCoordinateFromCity(City city)
{
	return city->y;
}

City *initCitiesArray(size_t n)
{
	City *citiesArray = (City *)malloc(n * sizeof(City));

	if (!wasAllocated(citiesArray))
		return NULL;

	return citiesArray;
}

City *getCitiesArrayFromTSP(TravellingSalesmanProblem tsp)
{
	return tsp->citiesArray;
}

void destroyCitiesArray(City *array, size_t n)
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

void readTSPFile(char *fileName, TravellingSalesmanProblem tsp)
{
	FILE *file = fopen(fileName, "r");
	if (file == NULL)
	{
		printf("File %s not found!\n", fileName);
		exit(EXIT_FAILURE);
	}

	char line[MAX_LINE_LENGTH];
	while (fgets(line, sizeof(line), file) != NULL)
	{
		char name[MAX_LINE_LENGTH] = "";
		int dimension = 0;
		char fileType[MAX_LINE_LENGTH] = "";
		char edgeWeightType[MAX_LINE_LENGTH] = "";

		if (sscanf(line, "NAME: %[^\n]", name) == 1)
		{
			strcpy(tsp->name, name);
		}
		else if (sscanf(line, "TYPE: %[^\n]", fileType) == 1)
		{
			if (strcmp(fileType, "TSP") != 0)
			{
				printf("File Type %s is different of 'TSP'!\n", fileType);
				exit(EXIT_FAILURE);
			}
		}
		else if (sscanf(line, "DIMENSION: %d", &dimension) == 1)
		{
			tsp->dimension = dimension;
			tsp->citiesArray = initCitiesArray(tsp->dimension);
		}
		else if (sscanf(line, "EDGE_WEIGHT_TYPE: %[^\n]", edgeWeightType) == 1)
		{
			if (strcmp(edgeWeightType, "EUC_2D") != 0)
			{
				printf("Edge Weight Type %s is different of 'EUC_2D'!\n", edgeWeightType);
				exit(EXIT_FAILURE);
			}
		}
		else if (strcmp(line, "NODE_COORD_SECTION\n") == 0)
		{
			while (fgets(line, sizeof(line), file))
			{
				if (strcmp(line, "EOF") == 0)
					break;
				else
				{
					int cityId = 0;
					float x = 0.0, y = 0.0;
					if ((sscanf(line, "%d %f %f", &cityId, &x, &y) == 3) && cityId <= tsp->dimension)
					{
						*(tsp->citiesArray + idToPos(cityId)) = createCity(cityId, x, y);
					}
				}
			}
		}
	}

	fclose(file);
}
