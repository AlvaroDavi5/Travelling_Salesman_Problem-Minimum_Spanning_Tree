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
	float **citiesDistanceMatrix;
	City *citiesArray;
};

TravellingSalesmanProblem initTSP()
{
	TravellingSalesmanProblem tsp = (TSP *)malloc(sizeof(TSP));

	if (!wasAllocated(tsp))
		return NULL;

	tsp->name = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));
	tsp->dimension = 0;
	tsp->citiesDistanceMatrix = NULL;
	tsp->citiesArray = NULL;

	return tsp;
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
			tsp->citiesDistanceMatrix = initCitiesDistanceMatrix(tsp->dimension);
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
				{
					calculateDistanceBetweenCities(tsp);
					break;
				}
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

void destroyTSP(TravellingSalesmanProblem tsp)
{
	safeFree(tsp->name);
	destroyCitiesArray(tsp->citiesArray, tsp->dimension);
	destroyCitiesDistanceMatrix(tsp->citiesDistanceMatrix, tsp->dimension);

	safeFree(tsp);
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

float **initCitiesDistanceMatrix(size_t n)
{
	if (n < 1)
		return NULL;

	float **matrix = (float **)malloc(n * sizeof(float *));

	if (!wasAllocated(matrix))
		return NULL;

	for (size_t i = 0; i < n; i++)
	{
		*(matrix + i) = (float *)malloc(n * sizeof(float));

		if (!wasAllocated(matrix + i))
		{
			safeFree(matrix);
			return NULL;
		}

		for (size_t j = 0; j < n; j++)
		{
			if (i == j)
				*(*(matrix + i) + j) = 0.0;
			else
				*(*(matrix + i) + j) = (float)MAX_CITY_DISTANCE;
		}
	}

	return matrix;
}

float **getCitiesDistanceMatrixFromTSP(TravellingSalesmanProblem tsp)
{
	return tsp->citiesDistanceMatrix;
}

void calculateDistanceBetweenCities(TravellingSalesmanProblem tsp)
{
	for (int i = 0; i < tsp->dimension; i++)
	{
		City rowCity = tsp->citiesArray[i];

		for (int j = 0; j < tsp->dimension; j++)
		{
			City columnCity = tsp->citiesArray[j];

			float xDiff = diff(rowCity->x, columnCity->x);
			float yDiff = diff(rowCity->y, columnCity->y);
			float distance = (float)sqrt(pow(xDiff, 2) + pow(yDiff, 2));

			tsp->citiesDistanceMatrix[i][j] = distance;
		}
	}
}

void destroyCitiesDistanceMatrix(float **matrix, size_t n)
{
	if (wasAllocated(matrix))
	{
		for (size_t i = 0; i < n; i++)
		{
			safeFree(*(matrix + i));
		}

		safeFree(matrix);
	}
}

void printCitiesDistanceMatrix(float **matrix, size_t n)
{
	if (n < 1)
		return;

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; ++j)
		{
			printf("%.1f", matrix[i][j]);

			if (j < (n - 1))
				printf(", ");
		}

		printf("\n");
	}
}
