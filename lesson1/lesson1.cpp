#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int solution(int N)
{
    int maxGap = 0, gap = 0;

    while (N && ((N&1) == 0)) { N>>=1; }

    while (N) {
        if (N&1) {
            if (gap>maxGap) {
                maxGap = gap;
            }
            gap = 0;
        } else {
            gap++;
        }
        N>>=1;
    }

    return maxGap;
}

void usage()
{
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "    lesson1 -n <number>\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "-n : Number to be searched for gaps\n");
    fprintf(stderr, "\n");
}

int main(int argc, char **argv)
{
    long N = LONG_MIN, c;

    /* Parse the options */
    while ((c = getopt(argc, argv, "n:")) != -1) {
        switch (c) {
            case 'n':
                N = strtol(optarg, NULL, 0);
                break;
        }
    }

    if (N == LONG_MIN || N == LONG_MAX) {
        fprintf(stderr, "ERROR wrong parameter for option -n\n");
        usage();
        exit(1);
    }

    printf("%d\n", solution(N));
    return 0;
}
