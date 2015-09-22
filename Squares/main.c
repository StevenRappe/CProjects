/*  Steven Rappe
	main.c
*/

#include <stdlib.h>
#include <stdio.h>

#include "square1.h"
#include "square2.h"
#include "diamond.h"

void clearInputBuffer() {
  while ( getchar() != '\n' );
}

int main() {
  int size = 0, numInts=0;
  char **square;

  // Problem 1. Fixed-size square
  printf("Problem 1 (a square of size 10):\n");
  print10Square();

  // Problem 2. Flexible-size square
  printf("\nProblem 2:\n"); 
  while (numInts != 1 || size < 2 || size > 10) {
    printf("Please enter the size of the square [2-10]: ");
    numInts = scanf("%d", &size);
    clearInputBuffer();
  }
  allocateNumberSquare( (const int) size, &square );
  initializeNumberSquare( (const int) size, square );
  printNumberSquare( (const int) size, square );

  // Problem 3
  printf("\nProblem 3:\n");
  printNumberDiamond( (const int) size, square );

  // Free memory allocated earlier
  deallocateNumberSquare( (const int) size, square );

  return 0;
}

