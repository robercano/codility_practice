#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int solution(int A[], int N)
{
}

void usage()
{
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "    lesson3 -n <length> [-s <seed>]\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "-n : Size of the array. Must be an odd number\n");
    fprintf(stderr, "-s : Seed to be used for the RNG\n");
    fprintf(stderr, "\n");
}

int main(int argc, char **argv)
{
    long N = LONG_MIN, c;
    int seed = 0;
    int *A = NULL;

    /* Parse the options */
    while ((c = getopt(argc, argv, "n:s:")) != -1) {
        switch (c) {
            case 'n':
                N = strtol(optarg, NULL, 0);
                break;
            case 's':
                seed = strtol(optarg, NULL, 0);
                break;
        }
    }

    if (N == LONG_MIN || N == LONG_MAX || N%2 != 1) {
        fprintf(stderr, "ERROR wrong parameter for option -n\n");
        usage();
        exit(1);
    }

    A = (int*)malloc(N);
    if (A == NULL) {
        fprintf(stderr, "ERROR allocating memory for array\n");
        exit(1);
    }

    srand(seed);

    for (int i=0; i<N; i+=2) {
        A[i] = A[i+1] = random();
    }
    A[N-1] = random();

    for (int i=0; i<N; i++) {
        int posA = random() % N;
        int posB = random() % N;

        int swap = A[posA];
        A[posA] = A[posB];
        A[posB] = swap;
    }

    printf("%d\n", solution(A, N));
    return 0;
}
