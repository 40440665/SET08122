#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variable declarations
int diff; // Variable to store the difficulty
int solved = 0;
int row;
int column;
int value;
int movesCounter = 0;
int undoCounter = 0;
int redoCounter = 0;



int startChoice = 0;
int sudokuGrid [9][9]=	{{2,0,4,0,0,6,8,0,7}, //for storing the sudoko values
			 {0,5,0,0,1,4,0,6,3},
			 {0,8,0,3,7,2,0,5,0},
			 {5,0,9,0,8,0,7,3,0},
			 {6,0,8,7,0,3,5,0,0},
			 {7,2,0,0,9,5,0,8,0},
			 {3,9,0,0,0,0,1,4,0},
			 {4,0,5,1,0,8,0,2,0},
			 {0,6,0,2,0,9,3,7,0}};
						
int savedSudokuGrid [9][9]=	{{2,3,4,9,5,6,8,1,7}, //KEY OF THE ABOVE SUDOKO
	     {9,5,7,8,1,4,2,6,3},
	     {1,8,6,3,7,2,4,5,9},
	     {5,4,9,6,8,1,7,3,2},
	     {6,1,8,7,2,3,5,9,4},
	     {7,2,3,4,9,5,6,8,1},
	     {3,9,2,5,6,7,1,4,8},
	     {4,7,5,1,3,8,9,2,6},
	     {8,6,1,2,4,9,3,7,5}};
						
						
						
						
struct timerSettings
{
    int timerOption;		// Variable to store whether the player wants a timer or not
	int timerLength;		// Variable to store the length of the timer
};

struct stack
{
	int array[15];
	int top;
};

struct stack undoRowStack;
struct stack undoColumnStack;
struct stack undoValueStack;

struct stack redoRowStack;
struct stack redoColumnStack;
struct stack redoValueStack;

typedef struct timerSettings Struct;
void welcomeScreen();
int diffSelect();
struct timerSettings timerSelect();
void printGameBoard();
void insertIntoGrid(int, int, int);
void playGame(int);
void rules();
void saveGame();
int isSolved();
void loadSudoku();
void generateSudoku(int);
int solveSudoku(int [][9], int, int);
int isAvailable(int [][9], int, int, int);

void undo();
void redo();
void init_stack(struct stack *);
void push(struct stack *, int item);
int *pop(struct stack *);





//Main method
void main()
{
	while(1)
	{
		welcomeScreen();
		switch(startChoice)
		{
		case 1:playGame(0);//TO PLAY A NEW GAME
	     break;
		case 2:playGame(1);//TO LOAD THE LAST GAME
	     break;
		case 3:rules();//TO SHOW THE RULES
	     break;
		case 4:exit(0);//TO EXIT THE GAME
	     break;
		default:break;
		}
	}
}




void playGame(int load)
{
	int rowFlag = 1;
	int columnFlag = 1;
	int valueFlag = 1;
	int rowBuffer;
	int columnBuffer;
	int valueBuffer;
	int diff = 1;	// Difficulty defaults to Easy (1)
	init_stack(&undoRowStack);
	init_stack(&undoColumnStack);
	init_stack(&undoValueStack);
	init_stack(&redoRowStack);
	init_stack(&redoColumnStack);
	init_stack(&redoValueStack);

	
	if(load == 1)
	{
		loadSudoku();
	}
	else if(load == 0)
	{
		diff = diffSelect();
		generateSudoku(diff);
	}
	
	struct timerSettings t = timerSelect();

	getchar();
	printf("Press ENTER to start the game:");
	getchar();

	while(1)
	{
		printGameBoard();
		do{
			printf("\n Please enter the row number (enter 100 to show the rules, 200 to save and quit to main menu or 300 to exit to main menu without saving)");
			printf("\n Or enter 22 to undo your last move or 33 to redo your last undo");
			printf("\n>");
			scanf(" %d", &rowBuffer);
			
			if(rowBuffer > 0 && rowBuffer < 10)
			{
				row = rowBuffer;
				rowFlag = 1;
			}
			else if(rowBuffer == 100)
			{
				rules();
				rowFlag = 0;
			}
			else if(rowBuffer == 200)
			{
				saveGame();
				goto mainMenu;
			}
			else if(rowBuffer == 300)
			{
				printf("\nEXITING....\n");
				goto mainMenu;
			}
			else if(rowBuffer == 22)
			{
				undo();
				printGameBoard();
				rowFlag = 0;
			}
			else if(rowBuffer == 33)
			{
				redo();
				printGameBoard();
				rowFlag = 0;
			}
			else
			{
				rowFlag = 0;
			}
			
		}while(rowFlag == 0);
			
		do{
			printf("\n Please enter the column number (enter 100 to show the rules, 200 to save and quit to main menu or 300 to exit to main menu without saving)");
			printf("\n>");
			scanf(" %d", &columnBuffer);
			if(columnBuffer > 0 && columnBuffer < 10)
			{
				column = columnBuffer;
				rowFlag = 1;
			}
			else if(columnBuffer == 100)
			{
				rules();
				columnFlag = 0;
			}
			else if(columnBuffer == 200)
			{
				saveGame();
				goto mainMenu;
			}
			else if(columnBuffer == 300)
			{
				printf("EXITING....");
				goto mainMenu;
			}
			else
			{
				columnFlag = 0;
			}
		}while(columnFlag == 0);
			
		do{
			printf("\n Please enter the value you want to insert into this grid position (enter 100 to show the rules, 200 to save and quit to main menu or 300 to exit to main menu without saving)");
			printf("\n>");
			scanf(" %d", &valueBuffer);
			
			if(valueBuffer > 0 && valueBuffer < 10)
			{
				value = valueBuffer;
			}
			else if(valueBuffer == 100)
			{
				rules();
				valueFlag = 0;
			}
			else if(valueBuffer == 200)
			{
				saveGame();
				goto mainMenu;
			}
			else if(valueBuffer == 300)
			{
				printf("EXITING....");
				goto mainMenu;
			}
			else
			{
				valueFlag = 0;
			}
		}while(valueFlag == 0);
			
		insertIntoGrid(row, column, value);
		

		
		solved = isSolved();
		
		printf("%d", solved);
		
		if (solved == 1)
		{
			printf("\n CONGRATULATIONS!!!!!!\n");
			mainMenu:
			break;
		}
	}
}



int isSolved()
{
	int solved = 0;
	int numOfGridsSolved = 0;
	int a,b,c,d,e,f,g,h;
	
	for(a = 0; a < 9; a++)
	{
		for(b = 0; b < 9; b++)
		{
			g = 0;
			h = 0;
			for(c = 0; c < 9; c++)
			{
				if(sudokuGrid[a][b]==sudokuGrid[a][c])
				{
					g++;
				}
				if(sudokuGrid[b][a]==sudokuGrid[c][a])
				{
					h++;
				}
			}
			if(g==1)
			{
				numOfGridsSolved++;
			}
			if(h==1)
			{
				numOfGridsSolved++;
			}
		}
	}
	
	for(a = 0; a < 9;)
	{
		for(b = 0; b < 9;)
		{
			for(c = a; c < a+3; c++)
			{
				for(d = b; d < b+3; d++)
				{
					g = 0;
					for(e = a; e < a+3; e++)
					{
						for(f = b; f < b+3; f++)
						{
							if(sudokuGrid[c][d] == sudokuGrid[e][f])
							{
								g++;
							}
						}
					}
					if(g == 1)
					{
						numOfGridsSolved++;
					}
				}
			}
			b = b + 3;
		}
		a = a + 3;
	}
		
	for(a=0;a<9;a++)
	{
		for(b=0;b<9;b++)
		{
			if(sudokuGrid[a][b] == 0)
			{
				numOfGridsSolved--;
			}
		}
	}
	
	if(numOfGridsSolved == 243)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}




































// Method to print the applications welcome screen
void welcomeScreen()
{
	printf("\t  ___                           \n");
	printf("\t |             |      | /       \n");
	printf("\t |___        __|  __  |/        \n");
	printf("\t     | |  | |  | |  | |\\  |  | \n");
	printf("\t  ___| |__| |__| |__| | \\ |__| \n\n");
	printf("\t\t Press ENTER to Begin:");
	getchar();
	
	do{
		printf("\n");
		printf("Please select from the following (Enter the number of your choice): \n");
		printf("\t\t 1) START NEW GAME\n");
		printf("\t\t 2) LOAD LAST GAME\n");
		printf("\t\t 3) RULES\n");
		printf("\t\t 4) EXIT\n");
		printf("\n>");

		// Read in and store value
		scanf(" %d", &startChoice);

		if(startChoice < 1 || startChoice > 4)
		{
			printf("\n\tThe number entered is unvalid (Please enter 1, 2, 3 or 4)");
		}

	}while(startChoice < 1 || startChoice > 4);
}




// Method that prompts the user to select a difficulty
int diffSelect()
{
	do{
		// Print the difficulty choices and prompt for difficulty selection
		printf("\n");
		printf("Please select a difficult from the following (Enter the number of your choice): \n");
		printf("\t\t 1) Easy\n");
		printf("\t\t 2) Intermediate\n");
		printf("\t\t 3) Hard\n");
		printf("\n>");

		// Read in value
		scanf(" %d", &diff);

		if(diff < 1 || diff > 3)
		{
			printf("\n\tThe number entered is unvalid (Please enter 1, 2 or 3)");
		}

	}while(diff < 1 || diff > 3);
	
	return diff;
}




// Method that prompts the user to select timer settings
struct timerSettings timerSelect()
{
	struct timerSettings t;		// Create instance of a timerSettings Struct
	char buffer;		// Create a buffer string variable to temporarily hold user input
	char lengthBuffer[5];
	int timerChoiceFlag = 0;		// Flag to let the program know that a timer choice has been select correctly
	int timerLengthFlag = 0;		// Flag to let the program know that a timer choice has been select correctly
	int timerChoice;
	int timerLengthBuffer;

	do{
		// Prompt user if they would like a timer or not
		printf("\nWould you like your game to be timed? (y/n): \n");
		printf("\n>");

		// Read in value
		scanf(" %c", &buffer);

		if(buffer == 'y')
		{
			timerChoiceFlag = 1;
			t.timerOption = 1;

			do{
				// Prompt user for how long they want their timer to be
				printf("\nHow long would you like the timer to be? (Enter the number of your choice): \n");
				printf("\t\t 1) 10 Minutes\n");
				printf("\t\t 2) 20 Minutes\n");
				printf("\t\t 3) 30 Minutes\n");
				printf("\t\t 4) I want to enter my own timer length\n");
				printf("\n>");

				// Read in value
				scanf(" %c", &buffer);
				// Convert string to int and store in difficulty variable
				timerChoice = atoi(&buffer);

				if(timerChoice == 1)
				{
					timerLengthFlag = 1;
					t.timerLength = 10;
				}
				else if(timerChoice == 2)
				{
					timerLengthFlag = 1;
					t.timerLength = 20;
				}
				else if(timerChoice == 3)
				{
					timerLengthFlag = 1;
					t.timerLength = 30;
				}
				else if(timerChoice == 4)
				{
					printf("\nPlease enter the length of timer you would like: (Maximum timer length is 120 minutes)\n");
					printf("\n>");
					// Read in value
					scanf(" %d", &timerLengthBuffer);
					// Convert string to int and store in difficulty variable
					if(timerLengthBuffer > 120 || timerLengthBuffer < 0)
					{
						timerLengthFlag = 0;
					}
					else
					{
						timerLengthFlag = 1;
						t.timerLength = timerLengthBuffer;
					}
				}
			}while(timerLengthFlag == 0);
		}
		else if(buffer == 'n')
		{
			timerChoiceFlag = 1;
			t.timerOption = 0;
		}
	}while(timerChoiceFlag == 0);

	return t;
}

void printGameBoard()
{
	int i, j;
	printf("\n");
	printf("\t\t ----------------------------- \n");
	for(i=0;i<9;i++)//PRINT THE SUDOKO
	{
		printf("\t\t");
		for(j=0;j<9;j++)
		{
			if(j==0 || j==3 || j==6)
			{			
				printf("|");
			}
			printf(" %d ",sudokuGrid[i][j]);
		}
		printf("| \n");
		if(i==2||i==5)
		printf("\t\t --------+---------+--------- \n");
	}	
	printf("\t\t ----------------------------- \n");
	printf("\n");
}




void insertIntoGrid(int r, int c, int v)
{	
	int buffer;
	// Sudoku grid index starts from 0 so r and c must -1
	r = r - 1;
	c = c - 1;
	
	// Push row and column values onto their respective undo stacks
	push(&undoRowStack, r);
	push(&undoColumnStack, c);
	buffer = sudokuGrid[r][c];
	push(&undoValueStack, buffer);
	
	
	sudokuGrid[r][c] = v;
	movesCounter++;
}



void rules()
{
	printf("\n\n1) Each row must contain the numbers from 1 to 9, without repetitions\n");
	printf("2) Each column must contain the numbers from 1 to 9, without repetitions\n");
	printf("3) Each block must contain the numbers from 1 to 9, without repetitions\n");
	printf("4) The sum of every single row, column and block must equal 45\n\n");
}

void generateSudoku(int diff)
{
	int randBuffer;
	int randBuffer2;
	if(solveSudoku(sudokuGrid, 0, 0))
	{
		randBuffer = generateRandomNum();
		randBuffer2 = generateRandomNum();
		
		printf("%d", randBuffer);
		printf("%d", randBuffer2);
	}
}

int generateRandomNum()
{
    srand(time(NULL));
  
	return("%d", rand() % (9 - 0) + 0);
}


int solveSudoku(int sudoku[][9], int r, int c)
{
	int a;
	if(r < 9 && c < 9)
	{
		if(sudoku[r][c] != 0)
		{
			if((c+1) < 9)
			{
				return solveSudoku(sudoku, r, c+1);
			}
			else if((r+1) < 9)
			{
				return solveSudoku(sudoku, r+1, 0);				
			}
			else
			{
				return 1;
			}
		}
		else
		{
			for(a = 0; a < 9; ++a)
			{
				if(isGridAvailable(sudoku, r, c, a+1))
				{
					sudoku[r][c] = a+1;
					if((c+1) < 9)
					{
						if(solveSudoku(sudoku, r, c+1))
						{
							return 1;
						}
						else
						{
							sudoku[r][c] = 0;
						}
					}
					else if((r+1) < 9)
					{
						if(solveSudoku(sudoku, r+1, 0))
						{
							return 1;
						}
						else
						{
							sudoku[r][c] = 0;
						}
					}
					else
					{
						return 1;
					}
				}
			}
		}
		return 0;
	}
	else
	{
		return 1;
	}
}




int isGridAvailable(int sudoku[][9], int r, int c, int v)
{
	int startingR = (r/3) * 3;
	int startingC = (c/3) * 3;
	int a, b;
	
	for(a = 0; a < 9; ++a)
	{
		if(sudoku[r][a] == v)
		{
			return 0;
		}
		
		if(sudoku[a][c] == v)
		{
			return 0;
		}
		
		if(sudoku[startingR + (a%3)][startingC + (a/3)] == v)
		{
			return 0;
		}
	}
	return 1;
}





void saveGame()
{
	printf("\nGAME SAVED\n");
	
	for (int x=0 ; x < 9; x++)
	{
		for (int y=0 ; y < 9; y++)
		{
			savedSudokuGrid[x][y] = sudokuGrid[x][y];
		}
	}
}



void loadSudoku()
{
	for (int x=0 ; x < 9; x++)
	{
		for (int y=0 ; y < 9; y++)
		{
			sudokuGrid[x][y] = savedSudokuGrid[x][y];
		}
	}
}


void undo()
{
	int *rBuffer = NULL;
	int *cBuffer = NULL;
	int *vBuffer = NULL;
	int *vBuffer2 = NULL;


	undoCounter++;
	if(undoCounter > movesCounter)
	{
		printf("\nThere are no more moves to undo!\n");
		undoCounter--;
	}
	else
	{
		rBuffer = pop(&undoRowStack);
		cBuffer = pop(&undoColumnStack);
		vBuffer = pop(&undoValueStack);
		
		
		printf("%d", *rBuffer);
		printf("%d", *cBuffer);
		printf("%d", *vBuffer);

		vBuffer2 = sudokuGrid[*rBuffer][*cBuffer];

		sudokuGrid[*rBuffer][*cBuffer] = *vBuffer;
		
		push(&redoRowStack, *rBuffer);
		push(&redoColumnStack, *cBuffer);
		push(&redoValueStack, vBuffer2);
		
	}

}

void redo()
{
	int *rBuffer = NULL;
	int *cBuffer = NULL;
	int *vBuffer = NULL;
	int *vBuffer2 = NULL;

	redoCounter++;
	if(redoCounter > movesCounter)
	{
		printf("\nThere are no more moves to redo!\n");
		redoCounter--;
	}
	else
	{
		rBuffer = pop(&redoRowStack);
		cBuffer = pop(&redoColumnStack);
		vBuffer = pop(&redoValueStack);
		
		printf("%d", *rBuffer);
		printf("%d", *cBuffer);
		printf("%d", *vBuffer);

		vBuffer2 = sudokuGrid[*rBuffer][*cBuffer];

		sudokuGrid[*rBuffer][*cBuffer] = *vBuffer;

		
		push(&undoRowStack, *rBuffer);
		push(&undoColumnStack, *cBuffer);
		push(&undoValueStack, vBuffer2);
	}
	
}


// STACK API, used for the undo and redo features

void init_stack(struct stack *s)
{
	s->top = -1;
}

void push(struct stack *s, int item)
{
	if(s->top == 15-1)
	{
		printf("Stack is full. Couldnt push '%d' onto stack\n", item);
		return;
	}
	s->top++;
	s->array[s->top] = item;
}


int *pop(struct stack *s)
{
	int *data;
	if(s->top == -1)
	{
		printf("Stack is empty\n");
		return NULL;
	}
	data = &s->array[s->top];
	s->top--;
	return data;
}