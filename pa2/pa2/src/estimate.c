
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

double **transpose(double **X, int rows, int cols)
{
    double **A = (double **)malloc(cols * sizeof(double *));

    for (int i = 0; i < cols; i++)
    {
        A[i] = (double *)malloc(rows * sizeof(double));
        for (int j = 0; j < rows; j++)
        {
            A[i][j] = X[j][i];
        }
    }

    return A;
}

void releaseMatrix(double **matrix, int rows)
{
    int i;
    double *current;
    for (i = 0; i < rows; i++)
    {
        current = matrix[i];
        free(current);
        current = NULL;
    }
    free(matrix);
    matrix = NULL;
}

double **multiplyMatrix(double **mat, int row, int column, double **matrix1, int row1, int column1)
{
    if (column != row1)
    {
        return NULL;
    }
    else
    {
        double **result;
        result = (double **)malloc(row * sizeof(double *));
        for (int i = 0; i < row; i++)
        {
            result[i] = (double *)malloc(column1 * sizeof(double));
        }
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column1; j++)
            {
                result[i][j] = 0;
                for (int k = 0; k < column; k++)
                {
                    result[i][j] += (mat[i][k] * matrix1[k][j]);
                }
            }
        }
        return result;
    }
}

void displayMatrix(double **matrix, int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%0.0lf", matrix[i][j]);
        }
        printf("\n");
    }
    return;
}

double** predict(double** inputMatrix, int numRows1, int numCols1, double** coeffMatrix, int numRows2, int numCols2) {
    int i, j;
    double** resultMatrix;
    resultMatrix = (double**)malloc(numRows1 * sizeof(double*));

    for (i = 0; i < numRows1; i++) {
        resultMatrix[i] = (double*)malloc(1 * sizeof(double));
        resultMatrix[i][0] = inputMatrix[i][0];
    }

    for (i = 0; i < numRows1; i++) {
        for (j = 0; j < numRows2; j++) {
            if (j == 0) {
                resultMatrix[i][0] = coeffMatrix[j][0];
            }
            else {
                resultMatrix[i][0] += (coeffMatrix[j][0] * inputMatrix[i][j - 1]);
            }
        }
    }

    return resultMatrix;
}

double **inverse(double **matrix, int n)
{
    int i;
    int j;
    int k;
    int v;
    int count = n;
    double counter;
    double cols = 2 * n;
    double **matrixInv;
    matrixInv = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++)
    {
        matrixInv[i] = (double *)malloc(cols * sizeof(double));
    }
    double **finalinverse;
    finalinverse = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++)
    {
        finalinverse[i] = (double *)malloc(n * sizeof(double));
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < (cols); j++)
        {
            if (j == count)
            {
                matrixInv[i][j] = 1.000000;
            }
            else if (j > (n - 1))
            {
                matrixInv[i][j] = 0.000000;
            }
            else
            {
                matrixInv[i][j] = matrix[i][j];
            }
        }
        count++;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i > j)
            {
                continue;
            }
            if (i == j && matrixInv[i][j] != 1.000000)
            {
                counter = matrixInv[i][j];
                for (k = 0; k < (cols); k++)
                {
                    matrixInv[i][k] = matrixInv[i][k] / counter;
                }
                continue;
            }
            else if (i != j && matrixInv[j][i] != 0.000000)
            {
                for (v = j; v < n; v++)
                {
                    counter = matrixInv[v][i];
                    for (k = 0; k < (cols); k++)
                    {
                        matrixInv[v][k] = matrixInv[v][k] + ((-1 * counter) * matrixInv[j - 1][k]);
                    }
                }
                continue;
            }
        }
    }
    for (i = (n - 2); i > -1; i--)
    {
        for (j = (n - 1); matrixInv[i][j] != 1.000000; j--)
        {
            for (v = i; v > -1; v--)
            {
                counter = matrixInv[i][j];
                for (k = 0; k < (cols); k++)
                {
                    matrixInv[v][k] = matrixInv[v][k] + ((-1 * counter) * matrixInv[j][k]);
                }
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            finalinverse[i][j] = matrixInv[i][j + n];
        }
    }
    releaseMatrix(matrixInv, n);
    return finalinverse;
}

void displayMessage(const char *msg)
{
    printf("%s\n", msg);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        displayMessage("error");
        exit(0);
    }

    FILE *file1 = fopen(argv[1], "r");
    if (file1 == NULL)
    {
        exit(0);
    }

    FILE *file2 = fopen(argv[2], "r");
    if (file2 == NULL)
    {
        exit(0);
    }

    char word[10];
    int k;
    int n;
    int k1;
    int n1;
    int i, j;
    double num;

    fscanf(file1, "%s\n", word);
    fscanf(file2, "%s\n", word);
    fscanf(file1, "%d\n", &k);
    fscanf(file2, "%d\n", &k1);
    fscanf(file1, "%d\n", &n);
    fscanf(file2, "%d\n", &n1);

    double **X;
    X = (double **)malloc(n * sizeof(double *));
    int a;
    for (a = 0; a < n; a++)
    {
        X[a] = (double *)malloc((k + 1) * sizeof(double));
    }

    double **Y;
    Y = (double **)malloc(n * sizeof(double *));
    int b;
    for (b = 0; b < n; b++)
    {
        Y[b] = (double *)malloc(1 * sizeof(double));
    }

    double **Data;
    Data = (double **)malloc(n1 * sizeof(double *));

    int c;
    for (c = 0; c < n1; c++)
    {
        Data[c] = (double *)malloc(k1 * sizeof(double));
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < k + 2; j++)
        {
            if (j == 0)
            {
                X[i][j] = 1.0;
                if (i < n1)
                {
                    fscanf(file2, "%lf ", &num);
                    Data[i][j] = num;
                }
            }
            else if (j == k + 1)
            {
                fscanf(file1, "%lf\n", &num);
                Y[i][0] = num;
            }
            else
            {
                fscanf(file1, "%lf ", &num);
                X[i][j] = num;
                if (i < n1 && j == k1 - 1)
                {
                    fscanf(file2, "%lf\n", &num);
                    Data[i][j] = num;
                }
                else if (i < n1 && j < k1)
                {
                    fscanf(file2, "%lf ", &num);
                    Data[i][j] = num;
                }
            }
        }
    }

    fclose(file1);
    fclose(file2);

    double **transposeMatrix = transpose(X, n, k + 1);
    double **multMatrix = multiplyMatrix(transposeMatrix, (k + 1), n, X, n, (k + 1));
    double **inverseMatrix = inverse(multMatrix, k + 1);
    double **finishE = multiplyMatrix(inverseMatrix, k + 1, k + 1, transposeMatrix, k + 1, n);
    double **weights = multiplyMatrix(finishE, k + 1, n, Y, n, 1);
    double **housePrice = predict(Data, n1, k1, weights, k + 1, 1);

    displayMatrix(housePrice, n1, 1);

    releaseMatrix(X, n);
    releaseMatrix(Y, n);
    releaseMatrix(Data, n1);
    releaseMatrix(transposeMatrix, k + 1);
    releaseMatrix(multMatrix, k + 1);
    releaseMatrix(inverseMatrix, k + 1);
    releaseMatrix(finishE, k + 1);
    releaseMatrix(weights, k + 1);
    releaseMatrix(housePrice, n1);

    return 0;
}
