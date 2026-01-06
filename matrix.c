#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

/*
 * Reads a matrix from a file and stores it in a Matrix struct.
 * Parameters:
 *   filename - Path to the file containing the matrix.
 * Returns:
 *   A Matrix struct containing the matrix data.
 */
Matrix readMatrixFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    Matrix matrix;
    fscanf(file, "%d %d", &matrix.rows, &matrix.cols);

    if (matrix.rows != matrix.cols) {
        fprintf(stderr, "Error: Matrix must be square.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    matrix.data = (double **)malloc(matrix.rows * sizeof(double *));
    for (int i = 0; i < matrix.rows; i++) {
        matrix.data[i] = (double *)malloc(matrix.cols * sizeof(double));
        for (int j = 0; j < matrix.cols; j++) {
            fscanf(file, "%lf", &matrix.data[i][j]);
        }
    }

    fclose(file);
    return matrix;
}

/*
 * Recursively calculates the determinant of a matrix.
 * Parameters:
 *   matrix - The matrix whose determinant is to be calculated.
 * Returns:
 *   The determinant of the matrix.
 */
double calculateDeterminant(Matrix matrix) {
    if (matrix.rows == 1) {
        printf("Determinant of 1x1 matrix: %.2f\n", matrix.data[0][0]);
        return matrix.data[0][0];
    }

    if (matrix.rows == 2) {
        double determinant = (matrix.data[0][0] * matrix.data[1][1]) -
                             (matrix.data[0][1] * matrix.data[1][0]);
        printf("Determinant of 2x2 matrix: %.2f\n", determinant);
        return determinant;
    }

    double determinant = 0.0;
    for (int col = 0; col < matrix.cols; col++) {
        // Create a smaller matrix (minor)
        Matrix minor;
        minor.rows = matrix.rows - 1;
        minor.cols = matrix.cols - 1;
        minor.data = (double **)malloc(minor.rows * sizeof(double *));
        for (int i = 0; i < minor.rows; i++) {
            minor.data[i] = (double *)malloc(minor.cols * sizeof(double));
        }

        for (int i = 1; i < matrix.rows; i++) {
            int minorCol = 0;
            for (int j = 0; j < matrix.cols; j++) {
                if (j != col) {
                    minor.data[i - 1][minorCol] = matrix.data[i][j];
                    minorCol++;
                }
            }
        }

        double subDeterminant = calculateDeterminant(minor);
        printf("Sub-determinant for column %d: %.2f\n", col, subDeterminant);

        determinant += (col % 2 == 0 ? 1 : -1) * matrix.data[0][col] * subDeterminant;

        // Free the minor matrix
        for (int i = 0; i < minor.rows; i++) {
            free(minor.data[i]);
        }
        free(minor.data);
    }

    printf("Determinant for current matrix: %.2f\n", determinant);
    return determinant;
}



/*
 * Frees the memory used by a matrix.
 * Parameters:
 *   matrix - Pointer to the matrix to free.
 */
void freeMatrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    matrix->data = NULL;
}