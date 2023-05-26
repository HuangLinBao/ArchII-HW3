

#include <immintrin.h> // portable to all x86 compilers
#include <stdio.h>
#include <time.h>

#define DATA float

const int SIZE = 512;

DATA A[SIZE][SIZE];
DATA B[SIZE][SIZE];
DATA C[SIZE][SIZE];
DATA C2[SIZE][SIZE];
DATA C3[SIZE][SIZE];

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

void mat_mat_blocked_interchanged_32(DATA A[SIZE][SIZE], DATA B[SIZE][SIZE], DATA C[SIZE][SIZE])
{
    const int BLOCK_SIZE = 32; // Adjust block size based on cache size and data access patterns

    for (int i = 0; i < SIZE; i += BLOCK_SIZE)
    {
        for (int j = 0; j < SIZE; j += BLOCK_SIZE)
        {
            for (int k = 0; k < SIZE; k += BLOCK_SIZE)
            {
                for (int ii = i; ii < i + BLOCK_SIZE; ii++)
                {
                    for (int kk = k; kk < k + BLOCK_SIZE; kk++)
                    {
                        for (int jj = j; jj < j + BLOCK_SIZE; jj++)
                        {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

void mat_mat_blocked_interchanged_16(DATA A[SIZE][SIZE], DATA B[SIZE][SIZE], DATA C[SIZE][SIZE])
{
    const int BLOCK_SIZE = 16; // Adjust block size based on cache size and data access patterns

    for (int i = 0; i < SIZE; i += BLOCK_SIZE)
    {
        for (int j = 0; j < SIZE; j += BLOCK_SIZE)
        {
            for (int k = 0; k < SIZE; k += BLOCK_SIZE)
            {
                for (int ii = i; ii < i + BLOCK_SIZE; ii++)
                {
                    for (int kk = k; kk < k + BLOCK_SIZE; kk++)
                    {
                        for (int jj = j; jj < j + BLOCK_SIZE; jj++)
                        {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

int main()
{

    DATA r;
    double before, after;
    double conventionalTime;

    initialize_2d_array(A);
    initialize_2d_array(B);

    before = seconds();

    mat_mat(A, B, C);

    after = seconds();

    conventionalTime = after - before;
    printf("Conventional Time:%f\n", conventionalTime);

    before = seconds();

    mat_mat_blocked_interchanged_16(A, B, C2);

    after = seconds();

    double blocked_16 = after - before;
    printf("Blocked Interchange Optimization, size 16 Time:%f\n", blocked_16);

    printf("verification:%d\n\n", compare(C, C2));
    printf("improvement:%f\n", conventionalTime / blocked_16);

    before = seconds();

    mat_mat_blocked_interchanged_32(A, B, C3);

    after = seconds();
    double blocked_32 = after - before;

    printf("Blocked Interchange Optimization, size 32 Time:%f\n", blocked_32);

    printf("verification:%d\n\n", compare(C, C3));
    printf("improvement:%f\n", conventionalTime / blocked_32);

    return 0;
}