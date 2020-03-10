#include <stdio.h>
#define M 6 // Square Matrix Size
#if M > 0

void outputMatrix(int matrix[M][M]);

int main()
{
    int matrix[M][M] = {0};
    for(int i = M - 1; i >= 0; i--)
    {
        for(int j = 0 + (M - 1 - i); j < M; j++)
        {
            matrix[i][j] = 1;
        }
    }
    outputMatrix(matrix);
    return 0;
}

void outputMatrix(int matrix[M][M])
{
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < M; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

#else

    int main()
    {
        return -1;
    }

#endif

