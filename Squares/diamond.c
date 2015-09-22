/*  Steven Rappe
	diamond.c
*/

#include <stdio.h>
#include <stdlib.h>

// prints a diamond of size 2-10.
void printNumberDiamond(const int size, char **square) {

	int i, j, line=0, printCntr;
	int check = (size/2);
	int oddEven = (size%2);
	
	// odd squares.
	if (oddEven == 1) {
		for (i = 0; i < size; i++) {
			printCntr = 0;
			for (j = 0; j < size; j++) {
				if ((j >= check-line) && (j <= check+line)) {
					printf("%d", printCntr);
					printCntr++;
				}
				else {
					printf(" ");
				}
			}
			// odd conditionals.
			if (i >= check) {
				line--;
			}
			else {
				line++;
			}
			printf("\n");
		}
	}
	// even squares.
	else {
		for (i = 0; i < size; i++) {
			printCntr = 0;
			for (j = 0; j < size; j++) {
				if ((j >= check-line) && (j <= check+line)) {
					printf("%d", printCntr);
					printCntr++;
				}
				else {
					printf(" ");
				}
			}
			// even conditionals.
			if (i > (check-1)) {
				line--;
			}
			else if (i == (check-1)) {
				line = line;
			}
			else {
				line++;
			}
			printf("\n");
		}
	}
}