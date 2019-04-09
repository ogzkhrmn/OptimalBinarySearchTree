#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

void allocateArray(int **arr, int length) {
	int i;
	for ( i = 0; i <= length; i++)
	{
		arr[i] = (int*)calloc(length, sizeof(int));
	}
}

void calculate(int** mainArray, int* keyArray, int** rootArray, int i, int j) {
	int k, newWeight;
	int totalPriority = 0;
	int weight = INT_MAX;
	int position = 0;
	for (k = i; k < j; k++) {
		totalPriority += keyArray[k];
	}
	for (k = i; k < j; k++) {
		newWeight = mainArray[i][k] + mainArray[k+1][j] + totalPriority;
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
			createPrintArray(rootArray, printArray, rootArray[left][right] +1, right, size, step + 1);
			createPrintArray(rootArray, printArray, left, rootArray[left][right], size, step + 1);
		}
		
	}
}

int main() {

	int i, j, keyNumber;
	scanf("%d", &keyNumber);

	int *pKey, **mainArray, **rootArray, **printArray;

	pKey = (int*)malloc(keyNumber * sizeof(int));
	mainArray = (int**)calloc(keyNumber, sizeof(int*));
	rootArray = (int**)calloc(keyNumber, sizeof(int*));
	printArray = (int**)calloc(keyNumber, sizeof(int*));

	allocateArray(mainArray, keyNumber);
	allocateArray(rootArray, keyNumber);
	allocateArray(printArray, keyNumber);

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

	for  (i = 0; i <= keyNumber; i++)
	{
		if (i < keyNumber) {
			printf("\n%d elemani için olasilik giriniz.", i);
			scanf("%d", &pKey[i]);
		}
		
		mainArray[i][i] = 0;
		mainArray[i][i+1] = pKey[i];
		rootArray[i][i + 1] = i;
		
	}

	for (i = 2; i <= keyNumber; i++) {
		for (j = i - 2; j >= 0; j--) {
			calculate(mainArray, pKey, rootArray, j, i);
		}
	}

	createPrintArray(rootArray, printArray, 0, keyNumber, keyNumber + 1, 0);

	for (i = 0; i <= keyNumber; i++) {
		for (j = 0; j <= keyNumber; j++) {
			if (printArray[i][j] != -1 ) {
				printf("%d", printArray[i][j]);
			}
		}
		printf("\n");
	}

	return 1;
}