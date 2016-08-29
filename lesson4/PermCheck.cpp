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

int solution(vector<int> &A)
{
    int N = A.size();
    vector<int> hash;

    hash.resize(N, 0);

    for (int i=0; i<N; ++i) {
        int val = A[i]-1;

        if (val < 0 || val >= N || hash[val] != 0) {
            return 0;
        }

        hash[val] = 1;
    }

    return 1;
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

    if (N == LONG_MIN || N == LONG_MAX) {
        fprintf(stderr, "ERROR wrong parameter for option -n\n");
        usage(argv[0]);
        exit(1);
    }

    A.resize(N);
    srand(seed);

    for (int i=0; i<N; i++) {
        A[i] = i + 1;
    }

    bool isPerm = true;

    if (random()%2) {
        /* Break permutation */
        int val = A[random()%N];

        int pos = random()%N;

        if (A[pos] != val) {
            A[pos] = val;
            isPerm = false;
        }
    }

    for (int i=0; i<N; i++) {
        int posA = random() % N;
        int posB = random() % N;

        int swap = A[posA];
        A[posA] = A[posB];
        A[posB] = swap;
    }

    printf("%s\n", solution(A) == isPerm ? "Success!" : "Error");

    return 0;
}
