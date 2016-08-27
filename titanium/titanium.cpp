#pragma GCC optimize ("O3")

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <climits>
#include <unistd.h>
#include <sys/time.h>

using namespace std;

#define LEFT_PAREN  '('
#define RIGHT_PAREN ')'
#define MATCH_PAREN  '.'

//#define TIME

int solution(string &S, int K)
{
    int size = S.length();

    int stbuf[size+1];
    int *st = &stbuf[0];
    int *st_base = st + 1;

    char *str = &S[0];
    char *str_end = str + size;
    int streak = 0;

#ifdef TIME
    struct timeval start, end;
    gettimeofday(&start, NULL);
#endif

    stbuf[0] = 0;

    for (; str != str_end; ++str) {
        if (*str != RIGHT_PAREN || *st != LEFT_PAREN) {
            if (streak != 0) {
                *++st = streak;
                streak = 0;
            }
            *++st = *str;
        } else {
            streak += -2;
            st--;

            if (st >= st_base && *st < 0) {
                streak += *st--;
            }
        }
    }

    if (streak != 0) {
        *++st = streak;
    }

#ifdef TIME
    gettimeofday(&end, NULL);
    cout << "Time matching: " << ((end.tv_sec - start.tv_sec)*1000.0 + (end.tv_usec - start.tv_usec)/1000.0) << endl;
    gettimeofday(&start, NULL);
#endif

    /* Check the substrings */
    int maxLength = 0;

    int st_size = st-st_base+1;
    int *st_end = &stbuf[st_size + 1];

    for (int i=0; i<st_size; ++i) {
        int length = 0;
        int edits = K;

        if (stbuf[i] < 0) {
            continue;
        }

        st = &stbuf[i+1];

        for (int prevBracket=0; st!=st_end; ++st) {
            if (*st < 0) {
                length += -*st;
                continue;
            }
            if (edits == 0) {
                break;
            }

            if (*st == prevBracket) {
                length +=2;
                edits--;
                prevBracket = MATCH_PAREN;
            } else if (prevBracket == RIGHT_PAREN && *st == LEFT_PAREN) {
                if (edits < 2) {
                    break;
                }
                length +=2;
                edits -= 2;
                prevBracket = MATCH_PAREN;
            } else {
                prevBracket = *st;
            }
        }

        if (length > maxLength) {
            maxLength = length;
        }

        /* If we've reached the last position no point
         * on continuing processing */
        if (st == st_end) {
            break;
        }
    }
#ifdef TIME
    gettimeofday(&end, NULL);
    cout << "Time fixing: " << ((end.tv_sec - start.tv_sec)*1000.0 + (end.tv_usec - start.tv_usec)/1000.0) << endl;
#endif

    return maxLength;
}

void usage()
{
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "    titanium [-p <pattern> | -n <length> ] -k <rotations> [-s <seed>]\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "-p : Specifies the parenthesis pattern to be processed. Exclusive with -n option\n");
    fprintf(stderr, "-n : Specifies the length of the random pattern to be generated. Exclusive with -p option\n");
    fprintf(stderr, "-k : Maximum number of rotations to allow\n");
    fprintf(stderr, "-s : Seed to be used for the random pattern generation, only when used with -n\n");
    fprintf(stderr, "\n");
}

int main(int argc, char **argv)
{
    string S;
    int c;
    int N = -1, K = -1, seed = 0;

    /* Parse the options */
    while ((c = getopt(argc, argv, "p:n:k:s:")) != -1) {
        switch (c) {
            case 'p':
                S = optarg;
                break;
            case 'n':
                N = strtol(optarg, NULL, 0);
                break;
            case 'k':
                K = strtol(optarg, NULL, 0);
                break;
            case 's':
                seed = strtol(optarg, NULL, 0);
                break;
        }
    }

    if (N == LONG_MIN || N == LONG_MAX) {
        fprintf(stderr, "ERROR wrong parameter for option -n\n");
        usage();
        exit(1);
    }
    if (K == LONG_MIN || K == LONG_MAX) {
        fprintf(stderr, "ERROR wrong parameter for option -k\n");
        usage();
        exit(1);
    }
    if (seed == LONG_MIN || seed == LONG_MAX) {
        fprintf(stderr, "ERROR wrong parameter for option -s\n");
        usage();
        exit(1);
    }
    if (S.length() != 0 && N != -1) {
        fprintf(stderr, "ERROR -p and -n option cannot be used together\n");
        usage();
        exit(1);
    }
    if (S.length() == 0 && (N == -1 || K == -1)) {
        fprintf(stderr, "ERROR -n and -k options mandatory when -p is not used\n");
        usage();
        exit(1);
    }

    /* Generate the random pattern if required */
    if (S.length() == 0) {
        S.resize(N, 0);
        srand(seed);

        for (int i=0; i<N; ++i) {
            S[i] = random()%2 ? '(' : ')';
        }
    }

    int ret = solution(S, K);

    printf("%d\n", ret);
    return 0;
}
