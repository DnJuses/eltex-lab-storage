#include <stdio.h>
#include <stdlib.h>

int c_add(int, int);
int c_sub(int, int);
int c_mul(int, int);
int c_div(int, int);
void c_readUserValues(int *a, int *b);
void c_exit();

int main()
{
    // 1 - add
    // 2 - sub
    // 3 - mul
    // 4 - div
    // 5 - exit
    // other - exception
    int choice = 0;
    while(1)
    {
        system("clear");
        printf("|Integral Type Calculator|\n\n"
               " Type in the number of command you want to perform\n"
               " 1 - Addition\n"
               " 2 - Substraction\n"
               " 3 - Multiplication\n"
               " 4 - Division\n"
               " 5 - Exit\n\n"
               "Your choice: ");
        if(scanf("%d", &choice) == 1)
        {
            system("clear");
            int a = 0, b = 0;
            switch(choice)
            {
                case 1:
                printf("|Addition|\n\n");
                c_readUserValues(&a, &b);
                printf("Result: %d\n", c_add(a, b));
	        system("read -p 'Press ENTER to continue...' var");
                break;
                case 2:
                printf("|Substraction|\n\n");
                c_readUserValues(&a, &b);
                printf("Result: %d\n", c_sub(a, b));
		system("read -p 'Press ENTER to continue...' var");
                break;
                case 3:
                printf("|Multiplication|\n\n");
                c_readUserValues(&a, &b);
                printf("Result: %d\n", c_mul(a, b));
		system("read -p 'Press ENTER to continue...' var");
                break;
                case 4:
                printf("|Division|\n\n");
                c_readUserValues(&a, &b);
                printf("Result: %d\n", c_div(a, b));
     		system("read -p 'Press ENTER to continue...' var");
                break;
                case 5:
                c_exit();
                break;
                default:
                printf("Unknown command\n");
                system("read -p 'Press ENTER to continue...' var");
                continue;
            }
        }
    }
    return 0;
}

int c_add(int a, int b)
{
    return a + b;
}

int c_sub(int a, int b)
{
    return a - b;
}

int c_mul(int a, int b)
{
    return a * b;
}

int c_div(int a, int b)
{
    switch(b)
    {
        case 0:
            printf("Division by 0, returning -1\n");
            return -1;
        default:
            return a / b;
    }

}

void c_readUserValues(int *a, int *b)
{
    printf("First value: ");
    if(scanf("%d", a) == 1){};
    printf("Second value: ");
    if(scanf("%d", b) == 1){};
}

void c_exit()
{
    printf("Successfully exited the programm\n");
    exit(0);
}
