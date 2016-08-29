#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <climits>

using namespace std;

#define MAX_N 100000
#define MAX_VALUE 1000
#define MIN_VALUE -1000

template<typename T>
void printVector(T *v, int size) {
    if (size == 0) {
        return;
    }

    for (int i=0; i<size-1; ++i) {
        cout << v[i] << ", ";
    }
    cout << v[size-1] << endl;
}

template<typename T>
void printVector(vector<T> &v) {
    printVector(&v[0], v.size());
}

int solution(vector<int> &A)
{
    unsigned long sum = 0;
    unsigned long N = A.size();

    for (unsigned long i=0; i<N; ++i) {
        sum += A[i];
    }

    return (int)((N+2)*(N+1)/2 - sum);
}

void usage(char *name)
{
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "    %s -n <length> [-s <seed>]\n", name);
    fprintf(stderr, "\n");

    fprintf(stderr, "-n : Size of the array, between 2 and 100000\n");
    fprintf(stderr, "-s : Seed to be used for the RNG\n");
    fprintf(stderr, "\n");
}

int main(int argc, char **argv)
{

    long N = LONG_MIN, c;
    int seed = 0;
    vector<int> A;

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

    if (N == LONG_MIN || N == LONG_MAX || N>MAX_N || N<2) {
        fprintf(stderr, "ERROR wrong parameter for option -n\n");
        usage(argv[0]);
        exit(1);
    }

    A.resize(N);
    srand(seed);

    int gap = random() % N;

    for (int i=0, val=1; i<N; i++, val++) {
        if (i == gap) {
            val++;
        }
        A[i] = val;
    }

    for (int i=0; i<N; i++) {
        int posA = random() % N;
        int posB = random() % N;

        int swap = A[posA];
        A[posA] = A[posB];
        A[posB] = swap;
    }

    printf("%s\n", solution(A) == (gap+1) ? "Success!" : "Error");

    return 0;
}
