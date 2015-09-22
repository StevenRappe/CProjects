/*  Steven Rappe
	test.c
*/

#include <stdio.h>
#include <stdlib.h>

#include "diamond.h"
#include "square1.h"
#include "square2.h"

// clears input.
void clearInputBuffer() {
  while ( getchar() != '\n' );
}

// Performs function calls and handles user input.
int main() {

	char **square;
	int size=0, numInts=0;
	
	print10Square();
	
	printf("\nProblem 2:\n");
	
	while (numInts != 1 || size < 2 || size > 10) {
		printf("Please enter the size of the square [2-10]: ");
		numInts = scanf("%d", &size);
		clearInputBuffer();
	}
	
	allocateNumberSquare( (const int) size, &square);
	
	initializeNumberSquare( (const int) size, square);
	
	printNumberSquare( (const int) size, square);
	
	printf("\nProblem 3:\n");
	printNumberDiamond( (const int) size, square);
	
	deallocateNumberSquare( (const int) size, square);
	
	return 0;
}