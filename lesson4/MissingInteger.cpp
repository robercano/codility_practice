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
    int i;
    int N = A.size();
    vector<int> check;

    check.resize(N, 0);

    for (i=0; i<N; ++i) {
        if (A[i] < 1 || A[i] > N) {
            continue;
        }
        check[A[i] - 1] = 1;
    }

    for (i=0; check[i] == 1 && i<N; ++i);

    return i + 1;
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

    if (N == LONG_MIN || N == LONG_MAX || N < 1 || N > 100000) {
        fprintf(stderr, "ERROR wrong parameter for option -n\n");
        usage(argv[0]);
        exit(1);
    }

    A.resize(N);
    srand(seed);

    for (int i=0; i<N; i++) {
        A[i] = random()%(N+1);
    }

    printVector(A);

    printf("%d\n", solution(A));

    return 0;
}
