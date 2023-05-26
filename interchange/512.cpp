

#include <immintrin.h> // portable to all x86 compilers
#include <stdio.h>
#include <time.h>

#define DATA float

const int SIZE = 512;

DATA A[SIZE][SIZE];
DATA B[SIZE][SIZE];
DATA C[SIZE][SIZE];
DATA C2[SIZE][SIZE];

double seconds()
{

    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec + now.tv_nsec / 1000000000.0;
}

void initialize_array(DATA a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        a[i] = rand() % 2;
    }
}
void initialize_2d_array(DATA a[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            a[i][j] = rand() % 2;
        }
}

void zero_2d_array(DATA a[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            a[i][j] = 0;
        }
}

int compare(DATA A[SIZE][SIZE], DATA B[SIZE][SIZE])
{

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (A[i][j] != B[i][j])
                return 0;

    return 1;
}

void mat_mat(DATA A[SIZE][SIZE], DATA B[SIZE][SIZE], DATA C[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < SIZE; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void mat_mat_interchanged(DATA A[SIZE][SIZE], DATA B[SIZE][SIZE], DATA C[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int k = 0; k < SIZE; k++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// an old attempt to interchange between 3 loops that resulted in time being double the conventional time.

// void mat_mat_interchanged(DATA A[SIZE][SIZE], DATA B[SIZE][SIZE], DATA C[SIZE][SIZE])
// {
//     for (int j = 0; j < SIZE; j++)
//     {
//         for (int k = 0; k < SIZE; k++)
//         {
//             for (int i = 0; i < SIZE; i++)
//             {
//                 C[i][j] += A[i][k] * B[k][j];
//             }
//         }
//     }
// }

int main()
{

    DATA r;
    double before, after;
    double conventialTime;

    initialize_2d_array(A);
    initialize_2d_array(B);

    before = seconds();

    mat_mat(A, B, C);

    after = seconds();
    conventialTime = after - before;
    printf("Conventional Time:%f\n", conventialTime);

    before = seconds();

    mat_mat_interchanged(A, B, C2);

    after = seconds();
    double interchangedTime = after - before;

    printf("Interchanged Time:%f\n", interchangedTime);

    printf("verification:%d\n\n", compare(C, C2));
    printf("improvement:%f\n", conventialTime / interchangedTime);

    return 0;
}