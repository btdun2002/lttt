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
        float numerator, denominator;
        fscanf(file, "%f/%f", &numerator, &denominator);
        input_mat[i] = numerator / denominator;
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

    float check_sum = 0;
    for (int i = 0; i < m * n; i++)
    {
        check_sum += input_mat[i];
        if (check_sum > 1)
        {
            printf("Nhap sai ma tran");
            return -1;
        }
    }
    if (check_sum != 1)
    {
        printf("Nhap sai ma tran");
        return -1;
    }

    float *p_x = calloc(m, sizeof(float));
    float *p_y = calloc(n, sizeof(float));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            p_x[j] += input_mat[i * m + j];
            p_y[i] += input_mat[i * m + j];
        }
    }

    float h_x = 0, h_y = 0;

    for (int i = 0; i < m; i++)
    {
        h_x += -p_x[i] * log2f(p_x[i]);
    }
    printf("H(X) = %f\n", h_x);

    for (int i = 0; i < n; i++)
    {
        h_y += -p_y[i] * log2f(p_y[i]);
    }
    printf("H(Y) = %f\n", h_y);

    float *given_y_mat = calloc(m * n, sizeof(float));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            given_y_mat[i * m + j] = input_mat[i * m + j] / p_y[i];
        }
    }

    float *given_x_mat = calloc(m * n, sizeof(float));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            given_x_mat[i * m + j] = input_mat[i * m + j] / p_x[j];
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
    printf("H(X,Y) = %f\n", h_x_y);

    float i_x_y = h_y - h_given_x;
    printf("H(Y) - H(Y|X) = %f\nI(X;Y) = %f\n", i_x_y, i_x_y);

    if (m != n)
    {
        printf("Kich thuoc ma tran khong thoa man de tinh D(P(x)||P(y)), D(P(y)||P(x))");
        return -1;
    }

    float d_x_y = 0, d_y_x;
    for (int i = 0; i < m; i++)
    {
        d_x_y += p_x[i] * log2f(p_x[i] / p_y[i]);
        d_y_x += p_y[i] * log2f(p_y[i] / p_x[i]);
    }
    printf("D(P(x)||P(y)) = %f\nD(P(y)||P(x)) = %f\n", d_x_y, d_y_x);
}