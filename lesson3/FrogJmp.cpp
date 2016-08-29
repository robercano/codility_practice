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

int solution(int X, int Y, int D)
{
    return (Y - X + (D - 1))/D;
}

void usage(char *name)
{
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "    %s -x <number> -y <number> -d <number>\n", name);
    fprintf(stderr, "\n");

    fprintf(stderr, "-x : Initial position\n");
    fprintf(stderr, "-y : Final position\n");
    fprintf(stderr, "-d : Frog step\n");
    fprintf(stderr, "\n");
}

int main(int argc, char **argv)
{

    long X = LONG_MIN, Y = LONG_MIN, D = LONG_MIN;
    int c;

    /* Parse the options */
    while ((c = getopt(argc, argv, "x:y:d:")) != -1) {
        switch (c) {
            case 'x':
                X = strtol(optarg, NULL, 0);
                break;
            case 'y':
                Y = strtol(optarg, NULL, 0);
                break;
            case 'd':
                D = strtol(optarg, NULL, 0);
                break;
        }
    }

    if (X == LONG_MIN || X == LONG_MAX || X < MIN_VALUE || X > MAX_VALUE) {
        fprintf(stderr, "ERROR wrong parameter for option -x\n");
        usage(argv[0]);
        exit(1);
    }
    if (Y == LONG_MIN || Y == LONG_MAX || Y < MIN_VALUE || Y > MAX_VALUE) {
        fprintf(stderr, "ERROR wrong parameter for option -y\n");
        usage(argv[0]);
        exit(1);
    }
    if (D == LONG_MIN || D == LONG_MAX || D < MIN_VALUE || D > MAX_VALUE) {
        fprintf(stderr, "ERROR wrong parameter for option -d\n");
        usage(argv[0]);
        exit(1);
    }
    if (Y < X) {
        fprintf(stderr, "ERROR X value must be less or equal than Y value\n");
        usage(argv[0]);
        exit(1);
    }

    printf("%d\n", solution(X, Y, D));

    return 0;
}
