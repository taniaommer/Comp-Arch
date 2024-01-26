

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

void multiplyMatrices(long long A[MAX_SIZE][MAX_SIZE], long long B[MAX_SIZE][MAX_SIZE], long long C[MAX_SIZE][MAX_SIZE], int size, long long mod)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < size; k++)
            {
                C[i][j] = (C[i][j] + (A[i][k] * B[k][j]) % mod) % mod;
            }
        }
    }
}

void matrixPower(long long base[MAX_SIZE][MAX_SIZE], long long result[MAX_SIZE][MAX_SIZE], int size, int exp, long long mod)
{
    long long temp[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                result[i][j] = 1;
            }
            else
            {
                result[i][j] = 0;
            }
        }
    }
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            multiplyMatrices(result, base, temp, size, mod);
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    result[i][j] = temp[i][j];
                }
            }
        }
        multiplyMatrices(base, base, temp, size, mod);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                base[i][j] = temp[i][j];
            }
        }
        exp /= 2;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s input_file\n", argv[0]);
        return 1;
    }
    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile)
    {
        fprintf(stderr, "Error: Cannot open input file\n");
        return 1;
    }

    int dimension;
    fscanf(inputFile, "%d", &dimension);
    long long matrix[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            fscanf(inputFile, "%lld", &matrix[i][j]);
        }
    }

    int power;
    fscanf(inputFile, "%d", &power);
    fclose(inputFile);

    long long result[MAX_SIZE][MAX_SIZE];
    long long mod = 1000000007LL;
    matrixPower(matrix, result, dimension, power, mod);

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            printf("%lld", result[i][j]);
            if (j < dimension - 1)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
