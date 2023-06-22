#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    FILE *file = fopen("Bai1.txt", "r"); // Open the file in read mode
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return 1;
    }

    int m, n;
    fscanf(file, "%d %d", &m, &n); // Read the dimensions of the matrix

    float *input_mat = malloc(m * n * sizeof(float)); // Allocate memory for the matrix

    // Read the matrix elements from the file
    for (int i = 0; i < m * n; i++)
    {
        fscanf(file, "%f", &input_mat[i]);
    }

    fclose(file); // Close the file

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (input_mat[i * m + j] < 0 || input_mat[i * m + j] > 1)
            {
                printf("Nhap lai P(%d,%d)", i, j);
                return -1;
            }
        }
    }

    // float sum = 0;
    // for (int i = 0; i < m * n; i++)
    // {
    //     printf("%f", input_mat[i]);
    //     sum += input_mat[i];
    //     if (sum > 1)
    //     {
    //         printf("Nhap sai ma tran");
    //         return -1;
    //     }
    // }
    // if (sum != 1)
    // {
    //     printf("Nhap sai ma tran");
    //     return -1;
    // }

    float *big_x = calloc(m, sizeof(float));
    float *big_y = calloc(n, sizeof(float));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            big_x[j] += input_mat[i * m + j];
            big_y[i] += input_mat[i * m + j];
        }
    }

    float h_x = 0, h_y = 0;

    for (int i = 0; i < m; i++)
    {
        h_x += -big_x[i] * log2f(big_x[i]);
    }
    printf("H(X) = %f\n", h_x);

    for (int i = 0; i < n; i++)
    {
        h_y += -big_y[i] * log2f(big_y[i]);
    }
    printf("H(Y) = %f\n", h_y);

    float *given_y_mat = calloc(m * n, sizeof(float));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            given_y_mat[i * m + j] = input_mat[i * m + j] / big_y[i];
        }
    }

    float *given_x_mat = calloc(m * n, sizeof(float));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            given_x_mat[i * m + j] = input_mat[i * m + j] / big_x[j];
        }
    }

    float h_given_y = 0;
    for (int i = 0; i < m * n; i++)
        if (input_mat[i])
            h_given_y += -input_mat[i] * log2f(given_y_mat[i]);
    printf("H(X|Y) = %f\n", h_given_y);

    float h_given_x = 0;
    for (int i = 0; i < m * n; i++)
        if (input_mat[i])
            h_given_x += -input_mat[i] * log2f(given_x_mat[i]);
    printf("H(Y|X) = %f\n", h_given_x);

    float h_x_y = 0;
    for (int i = 0; i < m * n; i++)
        if (input_mat[i])
            h_x_y += -input_mat[i] * log2f(input_mat[i]);
    printf("H(X,Y) = %f", h_x_y);
}