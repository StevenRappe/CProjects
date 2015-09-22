/*  Steven Rappe
	square2.c
*/

#include <stdio.h>
#include <stdlib.h>

// allocates memory for the square.
void allocateNumberSquare(const int size, char ***square) {
	
	(*square) = (char**)malloc(size*sizeof(char*));
	int i;
	
	for (i = 0; i < size; i++) {
		(*square)[i] = (char*)malloc(size*sizeof(char));
	}
}

// creates the square.
void initializeNumberSquare(const int size, char **square) {

	int i, j;
	
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			square[i][j] = ('0' + j);
		}
	}		
}

// prints the square.
void printNumberSquare(const int size, char **square) {

	int i, j;
	char c;
	
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			c = square[i][j];

			printf("%c", c);
		}
		printf("\n");
	}
}

// deallocates memory for the square.
void deallocateNumberSquare(const int size, char **square) {
	
	int i;
	
	for (i = 0; i < size; i++) {
		free(square[i]);
	}
	free(square);
}

