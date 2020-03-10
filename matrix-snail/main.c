#include <stdio.h>
#define M 5 // Square Matrix Size
#if M > 0

void outputMatrix(int matrix[M][M]);
int main()
{
    int matrix[M][M] = {0};
    int count = 1;
    // m - full coils amount
    for(int m = 0; m < (M + 1) / 2 && count <= M*M; m++)
    {
        for(int i = 0 + m, j = 0 + m; j < M - m; j++) // Left Top Coil, from left to right
        {
            matrix[i][j] = count;
            count++;
        }
        count--;
        for(int i = 0 + m, j = M - 1 - m; i < M - m; i++) // Top Right Coil, from top to bottom
        {
            matrix[i][j] = count;
            count++;
        }
        count--;
        for(int i = M - 1 - m, j = M - 1 - m; j >= 0 + m; j--) // Bottom Right Coil, from right to left
        {
            matrix[i][j] = count;
            count++;
        }
        count--;
        for(int i = M - 1 - m, j = 0 + m; i >= 1 + m; i--) // Bottom Left Coil, from bottom to top
        {
          matrix[i][j] = count;
          count++;
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
