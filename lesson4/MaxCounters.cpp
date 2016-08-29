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

inline bool samesign(int x, int y)
{
    return (x>=0)^(y<0);
}
inline int min(int x, int y)
{
    return x < y ? x : y;
}
inline int max(int x, int y)
{
    return x > y ? x : y;
}


vector<int> solution(int N, vector<int> &A)
{
    vector<int> result;
    int maxPos = 0, maxVal = 0;
    int nextMaxVal = 0;
    int M = A.size();

    result.resize(N, 0);

    for (int i=0; i<M; ++i) {
        int val = A[i] - 1;

        /* Normal increment */
        if (val < N) {
            if (!samesign(result[val], nextMaxVal)) {
                result[val] = -maxVal;
            }
            nextMaxVal = (result[val]<0) ?
                         min(--result[val], nextMaxVal) :
                         max(++result[val], nextMaxVal);
            continue;
        }

        /* Max out all values */
        maxPos = i;
        maxVal = nextMaxVal;
        nextMaxVal *= -1;
    }

    /* Set the latest known max value */
    std::fill(result.begin(), result.end(), abs(maxVal));

    /* Now restart the process from the last known position */
    for (int i=maxPos; i<M; ++i) {
        result[A[i] - 1]++;
    }

    return result;
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

    long N = LONG_MIN, M = LONG_MIN, c;
    int seed = 0;
    int a[] = { 1, 6, 2, 6, 3, 6, 4, 6, 4, 6, 6};
    vector<int> A(a, a+11);

    /* Parse the options */
    while ((c = getopt(argc, argv, "n:m:s:")) != -1) {
        switch (c) {
            case 'n':
                N = strtol(optarg, NULL, 0);
                break;
            case 'm':
                M = strtol(optarg, NULL, 0);
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
    if (M == LONG_MIN || M == LONG_MAX || M < 1 || M > 100000) {
        fprintf(stderr, "ERROR wrong parameter for option -m\n");
        usage(argv[0]);
        exit(1);
    }

    /*
    A.resize(M);
    srand(seed);

    for (int i=0; i<M; i++) {
        A[i] = random()%(N+1) + 1;
    }
*/
    printVector(A);

    vector<int> ret = solution(5, A);
    printVector(ret);

    return 0;
}
