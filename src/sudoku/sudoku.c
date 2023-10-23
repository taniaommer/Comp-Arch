

#include <stdio.h>
#include <stdbool.h>

#define SIZE 9

void printSudoku(int sudoku[SIZE][SIZE])
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            printf("%d", sudoku[row][col]);
        }
        printf("\n");
    }
}

bool isSafe(int sudoku[SIZE][SIZE], int row, int col, int num)
{
    for (int x = 0; x < SIZE; x++)
    {
        if (sudoku[row][x] == num || sudoku[x][col] == num)
        {
            return false;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (sudoku[i + startRow][j + startCol] == num)
            {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(int sudoku[SIZE][SIZE])
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (sudoku[row][col] == 0)
            {
                for (int num = 1; num <= SIZE; num++)
                {
                    if (isSafe(sudoku, row, col, num))
                    {
                        sudoku[row][col] = num;
                        if (solveSudoku(sudoku))
                        {
                            return true;
                        }
                        sudoku[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool isAlmostComplete(int sudoku[SIZE][SIZE])
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (sudoku[row][col] == 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool isCorrect(int sudoku[SIZE][SIZE])
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (!isSafe(sudoku, row, col, sudoku[row][col]))
            {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    char *inputFile = argv[1];
    int sudoku[SIZE][SIZE];

    FILE *file = fopen(inputFile, "r");
    if (file == NULL)
    {
        printf("error\n");
        return 1;
    }

    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            char c;
            if (fscanf(file, " %c", &c) == 1)
            {
                if (c == '_')
                {
                    sudoku[row][col] = 0;
                }
                else
                {
                    sudoku[row][col] = c - '0';
                }
            }
            else
            {
                fclose(file);
                printf("error\n");
                return 1;
            }
        }
    }

    fclose(file);

    if (isAlmostComplete(sudoku))
    {
        if (solveSudoku(sudoku))
        {
            if (isCorrect(sudoku))
            {
                printf("solvable\n");
            }
            else
            {
                printf("unsolvable\n");
            }
        }
        else
        {
            printf("unsolvable\n");
        }
    }
    else
    {
        if (isCorrect(sudoku))
        {
            printf("correct\n");
        }
        else
        {
            printf("incorrect\n");
        }
    }
    return 0;
}
