#include <stdio.h>
#define M 5 // Square Matrix Size
#if M > 0

void outputMatrix(int matrix[M][M]);

int main()
{
    int matrix[M][M] = {{1,  2,  3,  4,  5},
                        {6,  7,  8,  9,  10},
                        {11, 12, 13, 14, 15},
                        {16, 17, 18, 19, 20},
                        {21, 22, 23, 24, 25}};
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
