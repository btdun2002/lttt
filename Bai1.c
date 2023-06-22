#include <stdio.h>
#include <stdlib.h>

float log2(float n)
{
    return log(n) / log(2);
}

int main()
{
    // (X,Y)
    int m = 0, n = 0;
    printf("Nhap so hang: ");
    scanf("%d", &m);
    printf("Nhap so cot: ");
    scanf("%d", &n);
    float *p = malloc(m * n * sizeof(float));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            do
            {
                printf("Nhap P(%d,%d)", i, j);
                scanf("%f", &p[i * m + j]);
                getchar();
            } while (p[i * m + j] < 0 || p[i * m + j] > 1);
        }
    }

    // float sum = 0;
    // for (int i = 0; i < m * n; i++)
    // {
    //     printf("%f", p[i]);
    //     sum += p[i];
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
            big_x[i] += p[i * m + j];
            big_y[j] += p[i * m + j];
        }
    }

    float h_x = 0, h_y = 0;
    for (int i = 0; i < m; i++)
    {
        h_x += log2(big_x[i]);
    }
    printf("H(X) = %f", h_x);
    for (int i = 0; i < n; i++)
    {
        h_y += log2(big_y[i]);
    }
    printf("H(Y) = %f", h_y);
}