#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <vector>
#include <set>
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

int solution(int X, vector<int> &A)
{
    int counter = 0, i = 0;
    int N = A.size();
    vector<int> hash;

    hash.resize(X, 0);

    for (; i<N && counter<X; ++i) {
        if (hash[A[i]-1] == 0) {
            counter++;
        }

        hash[A[i]-1] = 1;
    }

    return counter == X ? i-1 : -1;
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

    long N = LONG_MIN, X = LONG_MIN, c;
    int seed = 0;
    vector<int> A;

    /* Parse the options */
    while ((c = getopt(argc, argv, "x:n:s:")) != -1) {
        switch (c) {
            case 'n':
                N = strtol(optarg, NULL, 0);
                break;
            case 'x':
                X = strtol(optarg, NULL, 0);
                break;
            case 's':
                seed = strtol(optarg, NULL, 0);
                break;
        }
    }

    if (N == LONG_MIN || N == LONG_MAX || N < 1 || N > 100000) {
        fprintf(stderr, "ERROR wrong parameter for option -n\n");
        usage(argv[0]);
        exit(1);
    }
    if (X == LONG_MIN || X == LONG_MAX || X < 1 || X > 100000) {
        fprintf(stderr, "ERROR wrong parameter for option -x\n");
        usage(argv[0]);
        exit(1);
    }

    A.resize(N);
    srand(seed);

    for (int i=0; i<N; i++) {
        A[i] = random()%X + 1;
    }

    printVector(A);

    printf("%d\n", solution(X, A));

    return 0;
}
