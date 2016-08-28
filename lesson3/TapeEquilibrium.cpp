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
    int N = A.size();
    vector<int> leftToRight, rightToLeft;

    leftToRight.resize(N, 0);
    rightToLeft.resize(N, 0);

    leftToRight[0] = A[0];
    rightToLeft[N-1] = A[N-1];

    for (int i=1 ;i<N-1; ++i) {
        leftToRight[i] = leftToRight[i-1] + A[i];
        rightToLeft[N-i-1] = rightToLeft[N-i] + A[N-i-1];
    }
    leftToRight[N-1] = leftToRight[N-2] + A[N-1];
    rightToLeft[0] = rightToLeft[1] + A[0];

    int minVal = INT_MAX;

    for (int i=1 ;i<N; ++i) {
        int val = abs(leftToRight[i-1] - rightToLeft[i]);
        if (val < minVal) {
            minVal = val;
        }
    }

    return minVal;
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

    for (int i=0; i<N; i++) {
        A[i] = random() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
    }

    printf("%d\n", solution(A));

    return 0;
}
