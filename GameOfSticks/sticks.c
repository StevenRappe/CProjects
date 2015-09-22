/*	
	Steven Rappe
	sticks.c
	
	Game of Sticks Simulation
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>      
#include <string.h>


int getHumanChoice() {
    
	int num_chosen;
	 
	printf("Player 1: How many sticks do you take (1-3)? ");
	scanf("%d", &num_chosen);
	
	// Check for valid input.
	while ((num_chosen != 1) && (num_chosen != 2) && (num_chosen != 3)) {
		printf("Player 1: Incorrect input. How many sticks do you take (1-3)? ");
		scanf("%d", &num_chosen);
	}
	return num_chosen;
}


int getComputerChoice(int current_sticks) {
	
    int rand_choice;
	    
    // Winning strategy for computer.
	if ((2 <= current_sticks) && (current_sticks <= 4)) {
		rand_choice = (current_sticks - 1);
	}	
	else if ((6 <= current_sticks) && (current_sticks <= 8)) {
		rand_choice = (current_sticks - 5);
	}	
	else if ((10 <= current_sticks) && (current_sticks <= 12)) {
		rand_choice = (current_sticks - 9);
	}
	else if (current_sticks == 1) {
		rand_choice = current_sticks;
	}
	else {
		rand_choice = rand() % 3 + 1;
	}
    printf("Computer has selected %d sticks.\n", rand_choice);
    return rand_choice;
}


int main(int argc, char** argv) {

    int human, computer, number_sticks, player_turn;
	human = 1;
	computer = -1;
    
    srand (time(NULL));
    
    printf("Welcome to the game of sticks!\n");
    printf("How many sticks are there on the table initially (10-100)? ");
    scanf("%d", &number_sticks);
	
	// Check for valid input.
	while ((number_sticks > 100) || (number_sticks < 10)) {
		printf("Initial amount invalid. Enter a new amount (10-100). ");
		scanf("%d", &number_sticks);
	}
	player_turn = 1;
	 
	// Main game loop.
	while (number_sticks > 0) {
		printf("There are %d sticks on the board.\n", number_sticks);
		
		if (player_turn == 1) {
			number_sticks = (number_sticks - getHumanChoice());
			player_turn += computer;
		}	
		else if (player_turn == 0) {
			number_sticks = (number_sticks - getComputerChoice(number_sticks));
			player_turn += human;
		}	
	}		
    if (player_turn == 1) {
		printf("You Win!\n");
	}	
	else {
		printf("You Lose!\n");
	}	
    return 0;
}

