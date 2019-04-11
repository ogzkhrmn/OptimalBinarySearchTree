#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

void allocateArray(double **arr, int length) {
	int i;
	for (i = 0; i <= length; i++)
	{
		arr[i] = (double*)calloc(length, sizeof(double));
	}
}

void allocateArrayInt(int **arr, int length) {
	int i;
	for (i = 0; i <= length; i++)
	{
		arr[i] = (int*)calloc(length, sizeof(int));
	}
}

void calculate(double** mainArray, double* keyArray, int** rootArray, int i, int j) {
	int k;
	double newWeight;
	double totalPriority = 0;
	double weight = INT_MAX;
	int position = 0;
	for (k = i; k < j; k++) {
		totalPriority += keyArray[k];
	}
	for (k = i; k < j; k++) {
		newWeight = mainArray[i][k] + mainArray[k + 1][j] + totalPriority;
		if (newWeight < weight) {
			weight = newWeight;
			position = k;
		}
	}
	mainArray[i][j] = weight;
	rootArray[i][j] = position;
}

void createPrintArray(int** rootArray, int** printArray, int left, int right, int size, int step) {
	if (left < size && right < size && right >= 0 && left >= 0) {
		if (rootArray[left][right] != -1) {
			printArray[step][right] = rootArray[left][right];
			createPrintArray(rootArray, printArray, rootArray[left][right] + 1, right, size, step + 1);
			createPrintArray(rootArray, printArray, left, rootArray[left][right], size, step + 1);
		}

	}
}

int main() {
	//start initializing to variables.
	int i, j, keyNumber;
	printf("Eleman sayisini giriniz : ");
	scanf("%d", &keyNumber);

	double *pKey, **mainArray;
	char *pKeyValue;
	int **rootArray, **printArray, writedElement = 0;

	pKey = (double*)malloc(keyNumber * sizeof(double));
	pKeyValue = (char*)malloc(keyNumber * sizeof(char));
	mainArray = (double**)calloc(keyNumber, sizeof(double*));
	rootArray = (int**)calloc(keyNumber, sizeof(int*));
	printArray = (int**)calloc(keyNumber, sizeof(int*));

	allocateArray(mainArray, keyNumber);
	allocateArrayInt(rootArray, keyNumber);
	allocateArrayInt(printArray, keyNumber);
	//stop initializing to variables.

	//initialize to arrays
	for (i = 0; i <= keyNumber; i++) {
		for (j = 0; j <= keyNumber; j++) {
			printArray[i][j] = -1;
		}
	}
	for (i = 0; i <= keyNumber; i++) {
		for (j = 0; j <= keyNumber; j++) {
			rootArray[i][j] = -1;
		}
	}

	//read inputs from user
	for (i = 0; i <= keyNumber; i++)
	{
		if (i < keyNumber) {
			printf("\n%d elemani giriniz.", i);
			scanf(" %c", &pKeyValue[i]);
			printf("\n%d elemani için olasilik giriniz.", i);
			scanf("%lf", &pKey[i]);
		}

		mainArray[i][i] = 0;
		mainArray[i][i + 1] = pKey[i];
		rootArray[i][i + 1] = i;

	}

	//calculate costs.
	for (i = 2; i <= keyNumber; i++) {
		for (j = i - 2; j >= 0; j--) {
			calculate(mainArray, pKey, rootArray, j, i);
		}
	}

	//creating array for print to screen
	createPrintArray(rootArray, printArray, 0, keyNumber, keyNumber + 1, 0);

	//print to screen
	printf("Toplam masraf:%lf\n", mainArray[0][keyNumber]);
	for (i = 0; i <= keyNumber && writedElement <= keyNumber; i++) {
		for (j = 0; j <= keyNumber; j++) {
			if (printArray[i][j] != -1) {
				printf("%c", pKeyValue[printArray[i][j]]);
				writedElement++;
			}
		}
		printf("\n");
	}

	return 1;
}