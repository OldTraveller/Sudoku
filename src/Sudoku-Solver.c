#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

bool isFull(int [][9]);
void printGrid(int [][9]);
void sudokuSolver(int [][9]);
int *possibleEntries(int [][9], int, int );

clock_t start, end;
int main(void)
{
    start = clock();
    int row, coloumn;
    int sudokuGrid[9][9] = {0};
    printf("\tEnter The Elements\n\n");

    for(row = 0; row < 9; row++)
        for(coloumn = 0; coloumn < 9; coloumn++)
            scanf("%d", &sudokuGrid[row][coloumn]);

    sudokuSolver(sudokuGrid);   // call to the solving function
    printf("No solution exists for this puzzle.\n");
}


void sudokuSolver(int sudokuGrid[][9])
{
    int row = 0, coloumn = 0, flag = 0;
    int i = 0, j = 0;

    //checks if there are any unassigned/0 elements in the grid
    // if there are no unassigned cells then sudoku is solved.
    // else proceed further.
    if(isFull(sudokuGrid))
    {
        printGrid(sudokuGrid);
        return;
    }

    // iterates through the sudoku grid, and finds an unassigned cell
    for(row = 0; row < 9; row++)
    {
        for(coloumn = 0; coloumn < 9; coloumn++)
        {
            if(sudokuGrid[row][coloumn] == 0)
            {
                i = row;                // stores the index of the unassigned cell in i and j,
                j = coloumn;            // and breaks out of the two for loops.
                flag = 1;
                break;
            }
        }
        if(flag == 1)
            break;
    }

    // an array which stores all the possible values which the
    // unassigned cell can store.
    int *possibilities = possibleEntries(sudokuGrid, i, j);

    for(row = 1; row < 10; row++)
    {
        // if the possible value is positive and not zero then
        // assign it to the sudoku grid at i, j.
        if(possibilities[row] != 0)
        {
            sudokuGrid[i][j] = possibilities[row];
            sudokuSolver(sudokuGrid);               //recursive call to sudokuSolver.
        }
    }

    //backtracking, if there are no more possible values for given i, j.
    sudokuGrid[i][j] = 0;
}


// checks if there is any unassigned cell remaining
// in the sudoku grid.
bool isFull(int sudokuGrid[][9])
{
    int row, coloumn;

    for(row = 0; row < 9; row++)
        for(coloumn = 0; coloumn < 9; coloumn++)
        {
            if(sudokuGrid[row][coloumn] == 0)
                return false;
        }

    return true;
}

// prints the solution of the sudoku puzzle
void printGrid(int sudokuGrid[][9])
{
    end = clock();
    int row, coloumn;
    printf("\n\n\tSOLVED !\n   (%lf seconds)\n", (double)(end - start)/CLOCKS_PER_SEC);

    for(row = 0; row < 9; row++)
    {
        if(row % 3 == 0)
           printf(" +--------+--------+-------+\n");

        for(coloumn = 0; coloumn < 9; coloumn++)
        {
            if(coloumn % 3 == 0)
                printf(" | ");

            printf("%d ", sudokuGrid[row][coloumn]);

            if(coloumn == 8)
                printf("|");
        }

        printf("\n");
    }
    printf(" +--------+--------+-------+\n\n");
    exit(0);
}


// this function is used to create an array of possible values
// for the given unassigned cell in the sudoku grid.
int * possibleEntries(int sudokuGrid[][9], int i, int j)
{
    // malloc is used so that the array can be passed to
    // its calling function and is not destroyed when the function
    // terminates/returns.
    int *possibilities = malloc(10 * sizeof(int));

    int row = i, coloumn = j;

    //Assumes that every number is a possible value.
    for(row = 1; row < 10; row++)
        possibilities[row] = 1;

    // checks for possible values along the row.
    // if its a fixed/assigned value the possibility of
    //that value becomes 0.
    for(coloumn = 0; coloumn < 9; coloumn++)
    {
        if(sudokuGrid[i][coloumn] != 0)
            possibilities[sudokuGrid[i][coloumn]] = 0;
    }

    //checks for possible values along the coloumn.
    // if its a fixed/assigned value the possibility of
    //that value becomes 0.
    for(row = 0; row < 9; row++)
    {
        if(sudokuGrid[row][j] != 0)
            possibilities[sudokuGrid[row][j]] = 0;
    }

    //checks for possible values in a sub sudoku grid,i.e,
    // 3 X 3 grid.The expression, i - i % 3, is used for
    // obtaining the value fo the index for the start of
    // each 3 x 3 grid. e.g, if i = 5, (i - i % 3) = 3, which is
    // the row index for the start of the second 3 x 3 box.
    for(int tempi = 0, row = i - i % 3; tempi < 3; tempi++, row++)
        for(int tempj = 0, coloumn = j - j % 3; tempj < 3; tempj++, coloumn++)
        {
            if(sudokuGrid[row][coloumn] != 0)
                possibilities[sudokuGrid[row][coloumn]] = 0;
        }

    // assign the possible values to the possibilities array.
    for(row = 1; row < 10; row++)
    {
        if(possibilities[row] !=0)
            possibilities[row] = row;

        else
            possibilities[row] = 0;
    }

    return possibilities;
}
