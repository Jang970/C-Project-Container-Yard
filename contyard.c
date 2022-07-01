#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NUM_ROWS 8
#define NUM_COLS 8

#define VACANT 0
#define BOUNDARY -1
#define ENTRY -2
#define EXIT -3

/***********************************************************/
/***********************************************************/
/******* ADD THE REQUIRED FUNCTIONS BELOW THIS POINT *******/
/***********************************************************/
/***********************************************************/

// Your function definitions should go here...

/*
The function InitialiseFloor will initialise the 8x8 floor grid to be used in the game.
The 8x8 grid will consist of -1s in the boundaries, 0s are located within the grid and then 2 special elements that symbolise the entry and exit

This function takes three inputs:
 - input 1: 2D array to be initialised
 - input 2: Character that decides on which boundary the entry will be 'T' = Top , 'B' = Bottom , 'L' = Left and 'R' = Right -- entry and exit element will be on the same row or column
 - input 3: a number that will indicate how many rows down from the top or columns across the left the entry or exit will be placed.

 This function will have no output - void function

 assuming that sensible values will be inputted

 author: justin ang
*/
void InitialiseFloor(int floor[NUM_ROWS][NUM_COLS], char entryboundary, int index)
{
	// count variables
	int i, j;

	// initialise 8x8 2D array - boundary elements = boundary, other elements = vacant
	// iterate through all elements of 2D array
	for (i = 0; i < NUM_ROWS; i++) {
		for (j = 0; j < NUM_COLS; j++) {

			// if statement that checks if it is the first or final row or first or final column of a row
			if ((i == 0) || (i == (NUM_ROWS - 1) || (j == 0) || (j == (NUM_COLS - 1)))) {

				// set first and final row all to -1 
				floor[i][j] = BOUNDARY;

			}
			else {
				// otherwise, set to vacant - 0
				floor[i][j] = VACANT;

			}
		}
	}

	// if statements to check the value of entryboundary to determine where to place entry and exit in the 2D array 
	// if the entry is to be place on the left boundary
	if (entryboundary == 'L') {

		// set left boundary row corresponding to index value to entry
		floor[index][0] = ENTRY;
		// set right boundary row corresponding to index value to exit
		floor[index][7] = EXIT;

	}

	// entry to be placed on the right boundary
	else if (entryboundary == 'R') {

		// set right boundary row == index to be entry
		floor[index][7] = ENTRY;
		// set left boundary row == index to be exit
		floor[index][0] = EXIT;

	}

	// entry to be placed on the top boundary
	else if (entryboundary == 'T') {

		// set top boundary column == index to be entry
		floor[0][index] = ENTRY;
		// set bottom boundary column == index to be exit
		floor[7][index] = EXIT;
	}

	// entry to be placed on bottom boundary
	else if (entryboundary == 'B') {

		// set bottom boundary column == index to be entry
		floor[7][index] = ENTRY;
		// set top boundary column == index to be exit
		floor[0][index] = EXIT;
	}


}

/*
The function PrintFloor will display the initialised floor grid in a more appropriate manner
input: - initialised 2D array containing floor grid

no outputs

This function will scan through the given 2D array and represent boundary elements with '@' , vacant elements with ' ', entry with 'U' and exit with 'X'
This is to then be outputted to the user
author: justin ang
*/
void PrintFloor(int floor[NUM_ROWS][NUM_COLS])
{
	// declare count variables
	int i, j;

	// nested for loop to iterate through 2D array
	for (i = 0; i < NUM_ROWS; i++) {
		for (j = 0; j < NUM_COLS; j++) {

			// conditional statements that will check the value of indexed element and assign to corresponding symbol
			if (floor[i][j] == BOUNDARY) {

				// if the element is -1 / BOUNDARY , '@' is printed
				printf("@");

			}
			else if (floor[i][j] == VACANT) {

				// if the element is 0 / VACANT, ' ' is printed
				printf(" ");

			}
			else if (floor[i][j] == ENTRY) {

				// if the element is -2 / ENTRY, 'U' is printed
				printf("U");

			}
			else if (floor[i][j] == EXIT) {

				// remaining element would be -3 / EXIT , 'X' is printed
				printf("X");

			}
			else if ((floor[i][j] >= 65) && (floor[i][j] <= 90)) {

				// this statement interprets the added values from addContainer and will print the ASCII equivalent to that value
				printf("%c", floor[i][j]);

			}

		}
		// new line for each row
		printf("\n");
	}
}


/*
The function FloorAreaAvailable will calculate the total amount of free area available in the floor space
All cells are said to have the same dimensions
If all available space is taken up then the function should show 0 area available

This function will take three inputs:
- input 1: 2D array with floor grid
- input 2: length of a single cell (in ft)
- input 3: width of a single cell (in ft)

This function has one output:
- output: double variable that contains the amount of free area available

author: justin ang
*/
double FloorAreaAvailable(int floor[NUM_ROWS][NUM_COLS], double length, double width)
{
	// initialise variable to return
	double free = 0;

	// declare indexing variables
	int i, j;

	//calculate the area of each grid cell
	double cellArea = length * width;

	// counting variable to determine how many free cells there are in the 2D array
	int freeCell = 0;

	// nested for loop to index 2D array
	for (i = 0; i < NUM_ROWS; i++) {
		for (j = 0; j < NUM_COLS; j++) {

			// conditional statement that checks if the corresponding element is equal to VACANT
			if (floor[i][j] == VACANT) {

				// add to count freeCell
				freeCell = freeCell + 1;

			}

		}
	}

	// calculate total area free by multiplying single grid area by number of free cells counted
	free = cellArea * freeCell;

	// return value of free
	return free;
}

// helper function declaration
void highestValue(int floor[NUM_ROWS][NUM_COLS], int* value);
int isValidVertical(int floor[NUM_ROWS][NUM_COLS], int row, int col, int size);
int isValidHorizontal(int floor[NUM_ROWS][NUM_COLS], int row, int col, int size);
/*
The function AddContainer will add 'containers' to the floor grid and every new container added will be assigned a corresponding letter depending on it's order of addition i.e container 1 = A, container B = 2 etc.
Containers can either be vertical or horizontal

This function will have four inputs:
- input 1: 2D array (floor grid)
- input 2: position of container (for vertical this is the top most part and for horizontal this is the left most part)
- input 3: container size
- input 4: direction of container ( 1 or 0 with 1 representing vertical)

no output

author: justin ang
*/
void AddContainer(int floor[NUM_ROWS][NUM_COLS], int position, int size, int direction)
{

	// initialise variables to store index position of row and column corresponding to position given
	int row = 0;
	int col = 0;

	// find corresponding row and column to given position 
	row = position / NUM_ROWS;
	col = position % NUM_COLS;

	// count variables
	int i, j;

	// nested for loop to index floor grid
	for (i = 0; i < NUM_ROWS; i++) {
		for (j = 0; j < NUM_COLS; j++) {

			// check direction if it is vertical or horizontal container - 0 = horizontal
			if (direction) {

				// if it is vertical
				// check if indexed element corresponds to row and col values and if that element is free 
				if ((i == row) && (j == col) && (floor[i][j] == 0)) {

					// have a helper function that will index array and find the highest value, then set indexed element to that value + 1

					// find a way to check from indexed element to given size if it will hit a boundary or entry/exit  - another helper function
					int validVertical = 0;

					// call helper function
					validVertical = isValidVertical(floor, row, col, size);

					if (validVertical) {
						// use a counter and a while loop to assign all values up to size
						// create variable that will correspond to the highest value in the array
						int highestVal = 64;

						// update highest value / find highest val
						highestValue(floor, &highestVal);

						int k = 0;
						while (k < size) {

							floor[i + k][j] = highestVal + 1;
							k++;

						}
					}

				}
			}
			else {

				// if it is horizontal
				if ((i == row) && (j == col) && (floor[i][j] == 0)) {

					// check if it will hit boundary, entry or exit 
					int validHorizontal = 0;

					validHorizontal = isValidHorizontal(floor, row, col, size);

					if (validHorizontal) {

						// create variable that will correspond to the highest value in the array
						int highestVal = 64;

						// update highest value / find highest val
						highestValue(floor, &highestVal);

						// set all columns up to value of size to highestVal
						int k = 0;
						while (k < size) {

							floor[i][j + k] = highestVal + 1;
							k++;

						}
					}


				}
			}
		}
	}
}

// helper function to determine highest value in array
void highestValue(int floor[NUM_ROWS][NUM_COLS], int* value) {

	// index array
	int i, j;

	int newVal = *value;

	for (i = 0; i < NUM_ROWS; i++) {
		for (j = 0; j < NUM_COLS; j++) {

			// if there is an element with a higher value
			if (floor[i][j] > *value) {

				// set currentValue to that number
				newVal = floor[i][j];
				*value = newVal;
			}

		}
	}

}

// helper function that will check if a VERTICAL container would be placed on a boundary, entry or exit 
int isValidVertical(int floor[NUM_ROWS][NUM_COLS], int row, int col, int size) {

	// return variable
	int isValid = 1;

	int k = 0;
	while (k < size) {

		if ((floor[row + k][col] == BOUNDARY) || (floor[row + k][col] == ENTRY) || (floor[row + k][col] == EXIT) || (floor[row + k][col] != 0)) {

			// if indexed element lands on the boundary or entry or exit or will hit existing containers, cannot print container
			isValid = 0;

		}

		k++;

	}

	return isValid;

}

// helper function that will check if a HORIZONTAL container would be placed on a boundary, entry or exit
int isValidHorizontal(int floor[NUM_ROWS][NUM_COLS], int row, int col, int size) {

	// return variable
	int isValid = 1;

	int k = 0;
	while (k < size) {

		if ((floor[row][col + k] == BOUNDARY) || (floor[row][col + k] == ENTRY) || (floor[row][col + k] == EXIT) || (floor[row][col + k] != 0)) {

			// if indexed element lands on the boundary or entry or exit, cannot print container
			isValid = 0;

		}

		k++;

	}

	return isValid;

}

// declare helper function that will find the first instance of char in the array
void findFirstInstance(int floor[NUM_ROWS][NUM_COLS], char character, int* row, int* col);

/*
The function LocateContainer will find the location of each placed container in the yard
This function will take six inputs:
- 2-D array showing the floor
- character that shows which container to look for
- pointer variable to store row in which container starts
- pointer variable to store column in which container starts
- pointer variable to store row in which container ends
- pointer variable to store column  in which container ends

This function has one output:
- integer which will determine if the container located is blocked from front and back: 0 = blocked from both directions , 1 = able to move at least one direction

author: justin ang
*/
int LocateContainer(int floor[NUM_ROWS][NUM_COLS], char move, int* rowStart, int* colStart, int* rowEnd, int* colEnd)
{
	// initialise variables to index 2D array
	int i, j;
	// initialise variable to return and will store 1 or 0 determining if the container is blocked or not
	int isBlocked = 1;

	// variables that will store the starting row and col of desired Char 
	int startingRow, startingCol;

	// variables to store ending row and col of wanted Char
	int endRow, endCol;

	// call helper function that will get values for startingRow and startingCol
	findFirstInstance(floor, move, &startingRow, &startingCol);

	// update pointer values
	*rowStart = startingRow;
	*colStart = startingCol;

	for (i = 0; i < NUM_ROWS; i++) {
		for (j = 0; j < NUM_COLS; j++) {

			// index searches for desired character and instead will keep going to the last element with desired character, respective i and j of that element will be put into rowEnd and colEnd
			if (floor[i][j] == move) {

				// update endRow and endCol to store i and j values respectively
				endRow = i;
				endCol = j;

			}

		}
	}

	// update pointers of rowEnd and colEnd
	*rowEnd = endRow;
	*colEnd = endCol;

	// find a way to check if top/bottom of container is blocked 
	// first find if the container is vertical or horizontal 
	// declare variable that will return a 1 if container is vertical, 0 if it is horizontal
	int isVertical = 0;

	// nested for loop to index through array from startingRow/Col to endingRow/Col of found char
	for (i = startingRow; i <= endRow; i++) {
		for (j = startingCol; j <= endCol; j++) {

			// checking if the next row also contains the char, then this means it is vertical
			if (floor[i + 1][j] == move) {

				// set variable to true
				isVertical = 1;

			}
			else if (floor[i][j + 1] == move) {

				// else if the char is located in the next column, the container is horizontal therefore isVertical is false
				isVertical = 0;

			}
		}
	}

	// next, depending on value of isVertical, check the cells above the front and below the end of vertical containers
	// for horizontal containers check to the left of the front and to the right of the end

	// if container is vertical
	if (isVertical) {

		// conditional statements to check cell before start and after end of container and if those cells are already occupied
		if ((floor[startingRow - 1][startingCol] != 0) && (floor[endRow + 1][endCol] != 0)) {

			// if occupied then container cannot move up or down so set isBlocked to 0
			isBlocked = 0;

		}

	}
	else {
		// if container is horizontal
		// checking cell to the left of start and to the right of end
		if ((floor[startingRow][startingCol - 1] != 0) && (floor[endRow][endCol + 1] != 0)) {

			// if both occupied container cannot move at all so isBlocked = 0
			isBlocked = 0;

		}
	}

	// return value of isBlocked
	return isBlocked;

}

// helper function to find where the desired char value first appears
void findFirstInstance(int floor[NUM_ROWS][NUM_COLS], char character, int* row, int* col) {

	// initialise indexing variables
	int i, j;

	// since nested for loops go row and then go through each column of that row, start row indexing from bottom most row
	for (i = NUM_ROWS; i >= 0; i--) {
		for (j = 0; j < NUM_COLS; j++) {

			// if matching element is found update variables pointed to and terminate loop
			if (floor[i][j] == character) {

				// update variables values pointed to i and j respectively
				*row = i;
				*col = j;
				break;

			}

		}
	}

}

// declare helper function that finds the last instance of where the container ends up
void findEndPosition(int floor[NUM_ROWS][NUM_COLS], int* row, int* col, int containerLetter);
// helper function that will find the first instance of where the container ends up
void findFrontPosition(int floor[NUM_ROWS][NUM_COLS], int* row, int* col, int containerLetter);

/*
the function MoveContainer will update the position of a container that we want to be moved

this function takes six inputs:
- 2D array that contains the floor
- four integer values with the first two representing the upper or left most part and the final two showing the right or bottom most part of the container we want to move
- integer value that indicates if the container is able to move or not

this function has an output:
- returns a 0 if the container is blocked
- returns 1 if the container is next to the entry (length-wise)
- retuns 2 if the container is next to the exit (length-wise)
- retuns -1 otherwise

how movement of the containers are determined:
- they move left or up is they can (horizontal containers move left if they can and vertical containers move up if they can) -- left/up movement are prioritized
- if they cannot move left or up, only then will they move down or up
- the containers will also move as far as they can i.e move until they hit a boundary or another container

author: justin ang
*/
int MoveContainer(int floor[NUM_ROWS][NUM_COLS], int r0, int c0, int r1, int c1, int isBlocked)
{
	// variable that stores what value the function will return
	int result = 0;

	// check if the container is horizontal or vertical
	// variable to store result
	int isVertical = 0;

	// indexing variables to use in looping through 2D array
	int i, j;

	// nested for loop that will start from r0,c0 (start of container) and go to r1,c1 (end of container)
	for (i = r0; i <= r1; i++) {
		for (j = c0; j <= c0; j++) {

			if (floor[i + 1][j] == floor[r1][c1]) { // checks if the container is vertical

				isVertical = 1;

			}
			else if (floor[i][j + 1] == floor[r1][c1]) { // checks if container is horizontal

				isVertical = 0;

			}

		}
	}

	// first check the value of isBlocked input and depending on value, do different actions
	if (isBlocked) { // if isBlocked = 1 i.e container is able to move

		// movement determined by orientation
		if (isVertical) { // if the container is vertical then it will prefer to first try move up

			// check if the container can move up
			if (floor[r0 - 1][c0] == VACANT) {

				// setting k to bottom most part of container
				int k = r1;
				// store value of what container is being moved
				int containerLetter = floor[r0][c0];

				// going through the container from bottom to top
				while (k >= r0) {

					// setting up variables used to index 2D array
					int i = r1;
					int j = c1;

					// variable that stores the very first value / bottom most value
					int initial = floor[r1][c1];

					// variable used in switching/moving elements
					int temp;

					// loop that will index through array and move elements as desired
					while (floor[i - 1][j] == VACANT || floor[i - 1][j] == initial) {

						// this chunk of code swaps position of indexed element with the position of the element above it - essentially moving it
						temp = floor[i - 1][j];
						floor[i - 1][j] = floor[i][j];
						floor[i][j] = temp;

						// update value / row
						i--;

					}

					// go to next row
					k--;
				}
				// keeping track of where the container will end up
				int endRowLocation, endColLocation, frontRowLocation, frontColLocation;

				// call helper function to find end part
				findEndPosition(floor, &endRowLocation, &endColLocation, containerLetter);

				// call helper function to find front part
				findFrontPosition(floor, &frontRowLocation, &frontColLocation, containerLetter);

				// now check adjacent cells of the front and back of container
				if (floor[frontRowLocation - 1][frontColLocation] == EXIT || floor[endRowLocation + 1][endColLocation] == EXIT) {
					result = 2;
				}
				else if (floor[frontRowLocation - 1][frontColLocation] == ENTRY || floor[endRowLocation + 1][endColLocation] == ENTRY) {
					result = 1;
				}
				else if (floor[frontRowLocation - 1][frontColLocation] == BOUNDARY || floor[endRowLocation + 1][endColLocation] == BOUNDARY) {
					result = 0;
				}
				else {
					result = 0;
				}

			}
			else { // container moves down

				// variable to store start/top of container 
				int k = r0;
				// store value of what container is being moved
				int containerLetter = floor[r0][c0];

				// ensure the movement is only done to the container / within container size
				while (k <= r1) {

					// initialise variables that store the start of container
					int i = r0;
					int j = c0;

					// this variable stores the value of the container being moved and will be used as a condition in the loop 
					int initial = floor[r0][c0];

					// this variable is used in the shifting of the elements and will store the value of the value of the element adjacent to the current element
					int temp;

					// this loop will ensure that the current element will move as far as possible and ensures that even if the next element is the same as the current indexed element it will still move
					while (floor[i + 1][j] == VACANT || floor[i + 1][j] == initial) {

						// shift elements down one by one
						temp = floor[i + 1][j];
						// set adjacent element to current element
						floor[i + 1][j] = floor[i][j];
						// set current element to previous value of adjacent element
						floor[i][j] = temp;

						// go to next row
						i++;

					}

					// increment through rows
					k++;
				}

				// keeping track of where the container will end up
				int endRowLocation, endColLocation, frontRowLocation, frontColLocation;

				// call helper function to find end part
				findEndPosition(floor, &endRowLocation, &endColLocation, containerLetter);

				// call helper function to find front part
				findFrontPosition(floor, &frontRowLocation, &frontColLocation, containerLetter);

				// now check adjacent cells of the front and back of container
				if (floor[frontRowLocation - 1][frontColLocation] == EXIT || floor[endRowLocation + 1][endColLocation] == EXIT) {
					result = 2;
				}
				else if (floor[frontRowLocation - 1][frontColLocation] == ENTRY || floor[endRowLocation + 1][endColLocation] == ENTRY) {
					result = 1;
				}
				else if (floor[frontRowLocation - 1][frontColLocation] == BOUNDARY || floor[endRowLocation + 1][endColLocation] == BOUNDARY) {
					result = 0;
				}
				else {
					result = 0;
				}
			}

		}
		else { // horizontal container movement

			// prefers to move left, so first check if it can move left
			if (floor[r0][c0 - 1] == VACANT) {

				// setting k to right most part of container
				int k = c1;
				// store value of what container is being moved
				int containerLetter = floor[r0][c0];

				// going through the container from right to left
				while (k >= c0) {

					// setting up variables used to index 2D array
					int i = r1;
					int j = c1;

					// variable that stores the very first value
					int initial = floor[r1][c1];

					// variable used in switching/moving elements
					int temp;

					// loop that will index through array and move elements as desired
					while (floor[i][j - 1] == VACANT || floor[i][j - 1] == initial) {

						// this chunk of code swaps position of indexed element with the position of the element to its left - essentially moving it
						temp = floor[i][j - 1];
						floor[i][j - 1] = floor[i][j];
						floor[i][j] = temp;
						// update value / column
						j--;

					}

					// go to next column
					k--;
				}

				// keeping track of where the container will end up
				int endRowLocation, endColLocation, frontRowLocation, frontColLocation;

				// call helper function to find end part
				findEndPosition(floor, &endRowLocation, &endColLocation, containerLetter);

				// call helper function to find front part
				findFrontPosition(floor, &frontRowLocation, &frontColLocation, containerLetter);


				// now check adjacent cells of the front and back of container
				if (floor[frontRowLocation][frontColLocation - 1] == EXIT || floor[endRowLocation][endColLocation + 1] == EXIT) {
					result = 2;
				}
				else if (floor[frontRowLocation][frontColLocation - 1] == ENTRY || floor[endRowLocation][endColLocation + 1] == ENTRY) {
					result = 1;
				}
				else if (floor[frontRowLocation][frontColLocation - 1] == BOUNDARY || floor[endRowLocation][endColLocation + 1] == BOUNDARY) {
					result = 0;
				}
				else {
					result = 0;
				}

			}
			else { // it must be able to only move right

				// variable to store start of container 
				int k = c0;
				// store value of what container is being moved
				int containerLetter = floor[r0][c0];

				// ensure the movement is only done to the container / within container size
				while (k <= c1) {

					// initialise variables that store the start of container
					int i = r0;
					int j = c0;

					// this variable stores the value of the container being moved and will be used as a condition in the loop 
					int initial = floor[r0][c0];

					// this variable is used in the shifting of the elements and will store the value of the value of the element adjacent to the current element
					int temp;

					// this loop will ensure that the current element will move as far as possible and ensures that even if the next element is the same as the current indexed element it will still move
					while (floor[i][j + 1] == VACANT || floor[i][j + 1] == initial) {

						// shift elements to the right one by one
						temp = floor[i][j + 1];
						// set adjacent element to current element
						floor[i][j + 1] = floor[i][j];
						// set current element to previous value of adjacent element
						floor[i][j] = temp;

						// increment column / go to next column
						j++;

					}

					// increment through columns
					k++;
				}

				// keeping track of where the container will end up
				int endRowLocation, endColLocation, frontRowLocation, frontColLocation;

				// call helper function to find end part
				findEndPosition(floor, &endRowLocation, &endColLocation, containerLetter);

				// call helper function to find front part
				findFrontPosition(floor, &frontRowLocation, &frontColLocation, containerLetter);

				// now check adjacent cells of the front and back of container
				if (floor[frontRowLocation][frontColLocation - 1] == EXIT || floor[endRowLocation][endColLocation + 1] == EXIT) {
					result = 2;
				}
				else if (floor[frontRowLocation][frontColLocation - 1] == ENTRY || floor[endRowLocation][endColLocation + 1] == ENTRY) {
					result = 1;
				}
				else if (floor[frontRowLocation][frontColLocation - 1] == BOUNDARY || floor[endRowLocation][endColLocation + 1] == BOUNDARY) {
					result = 0;
				}
				else {
					result = 0;
				}
			}

		}


	}
	else { // else isBlocked = 0 i.e cannot move

		// container cannot move, so check surrounding cells which will determine what output value will be
		// results will depend on orientation of the container as well

		// index through 2D array
		int k, z;

		for (k = 0; k < NUM_ROWS; k++) {
			for (z = 0; z < NUM_COLS; z++) {

				// multiple if statements to check multiple cases
				// first checking for vertical container and checking if it is next to another container or boundary
				if (isVertical) {

					// check if container is next to the exit
					if ((floor[r0 - 1][c0] == EXIT) || (floor[r1 + 1][c1] == EXIT)) {

						// update value of result when condition is met
						result = 2;


					}
					// checks if the container is next to the entry length-wise
					else if ((floor[r0 - 1][c0] == ENTRY) || (floor[r1 + 1][c1] == ENTRY)) {

						// update value of result when condition is met
						result = 1;

					}
					// container is either next to a boundary or blocked by other containers if the first two conditions are not met
					else {

						// result must be -1 here
						result = -1;

					}

				}
				else { // repeat conditionals for horizontal containers

					// check if container is next to the exit
					if ((floor[r0][c0 - 1] == EXIT) || (floor[r1][c1 + 1] == EXIT)) {

						// update value of result when condition is met
						result = 2;

					}
					else if ((floor[r0][c0 - 1] == ENTRY) || (floor[r1][c1 + 1] == ENTRY)) {

						// update value of result when condition is met
						result = 1;

					}
					// container is either next to a boundary or blocked by other containers if the first two conditions are not met
					else {

						// result must be -1 here
						result = -1;

					}

				}
			}
		}

	}

	return result;

}

// helper function to find where the container ends up
void findEndPosition(int floor[NUM_ROWS][NUM_COLS], int* row, int* col, int containerLetter) {

	// index through array
	int i, j;

	for (i = 0; i < NUM_ROWS; i++) {
		for (j = 0; j < NUM_COLS; j++) {

			// if matching integer is found then set values of i and j to row and column
			if (floor[i][j] == containerLetter) {

				*row = i;
				*col = j;

			}

		}
	}
}

// find front part of where the container ends up
void findFrontPosition(int floor[NUM_ROWS][NUM_COLS], int* row, int* col, int containerLetter) {

	// index through array
	int i, j;

	for (i = NUM_ROWS; i >= 0; i--) {
		for (j = 0; j < NUM_COLS; j++) {

			// if matching element is found update variables pointed to and terminate loop
			if (floor[i][j] == containerLetter) {

				// update variables values pointed to i and j respectively
				*row = i;
				*col = j;
				break;

			}

		}
	}

}

/***********************************************************/
/***********************************************************/
/********* DO NOT MODIFY ANY CODE BELOW THIS POINT *********/
/***********************************************************/
/***********************************************************/

/* Function to obtain capital letter as input */
char GetMove(void)
{
	char move;
	printf("\nMove container: ");
	scanf("%c", &move);
	// Ignore non-capital letter inputs
	while ((move < 'A') || (move > 'Z')) {
		scanf("%c", &move);
	}
	return move;
}

/* The main Container Yard simulation */
int main(void)
{
	int gameOver = 0;
	int isBlocked = 0;
	int floor[NUM_ROWS][NUM_COLS];
	int rowStart, colStart, rowEnd, colEnd;
	char input;

	/* Print banner */
	printf("............**********************************............\n");
	printf("............* CONTAINER YARD GAME SIMULATION *............\n");
	printf("............**********************************............\n");

	/* Initialise the yard floor grid and add containers */
	InitialiseFloor(floor, 'R', 3);
	AddContainer(floor, 27, 2, 0);
	AddContainer(floor, 9, 2, 0);
	AddContainer(floor, 17, 3, 0);
	AddContainer(floor, 26, 2, 1);
	AddContainer(floor, 42, 2, 1);
	AddContainer(floor, 36, 2, 1);
	AddContainer(floor, 51, 3, 0);
	AddContainer(floor, 13, 3, 1);
	AddContainer(floor, 22, 2, 1);

	/* Print status */
	printf("ENGGEN131 2021 - C Project\nContainer Yard!  The containers are rushing in!\n");
	printf("In fact, %.2f%% of the yard floor is available for containers!\n\n", FloorAreaAvailable(floor, 20.5, 10.3));

	/* Main simulation loop */
	while (gameOver != 2) {
		PrintFloor(floor);
		input = GetMove();
		isBlocked = LocateContainer(floor, input, &rowStart, &colStart, &rowEnd, &colEnd);
		gameOver = MoveContainer(floor, rowStart, colStart, rowEnd, colEnd, isBlocked);
	}

	/* A container is ready to exit - the simulation is over */
	PrintFloor(floor);
	printf("\nCongratulations, you've succeeded!");

	return 0;
}
