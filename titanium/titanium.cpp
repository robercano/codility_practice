#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <climits>
#include <unistd.h>

using namespace std;

#define LEFT_PAREN_MARK  -1
#define RIGHT_PAREN_MARK -2
#define MATCH_PAREN_MARK  1
#define UNKNW_PAREN_MARK  0

#define LEFT_PAREN  '('
#define RIGHT_PAREN ')'
#define MATCH_PAREN  '.'
#define UNKNW_PAREN  '?'

int solution(string &S, int K)
{
    int size = S.length();
    char st[size];
    int st_idx = -1;
    int pos[size];
    int pos_idx = -1;
    int fix[size];
    int fix_idx = -1;

    char *str = &S[0];
#ifdef STREAK
    int streak = 0;
#endif

    for (int i=0; i<size; ++i) {
        if ((st_idx != -1) && (st[st_idx] == LEFT_PAREN) && (str[i] == RIGHT_PAREN)) {
            str[i] = str[pos[pos_idx]] = MATCH_PAREN;

            st_idx--;
            pos_idx--;

#ifdef STREAK
            streak += 2;
#endif
        } else {
#ifdef STREAK
            if (fix_idx == -1 || fix[fix_idx] == LEFT_PAREN || fix[fix_idx] == RIGHT_PAREN) {
                fix[++fix_idx] = 0;
            }

            fix[fix_idx] += streak;
            streak = 0;

            fix[++fix_idx] = (S[i]=='(' ? LEFT_PAREN_MARK : RIGHT_PAREN_MARK);
#endif
            st[++st_idx] = S[i];
            pos[++pos_idx] = i;
        }
    }
#ifdef STREAK
    if (streak > 0) {
        if (fix_idx == -1 || fix[fix_idx] == LEFT_PAREN || fix[fix_idx] == RIGHT_PAREN) {
            fix[++fix_idx] = 0;
        }

        fix[fix_idx] += streak;
    }
    fix_idx++;
#endif

#ifndef STREAK
    fix_idx++;
    int length = 0;

    for (int i=0; i<size; ++i) {
        if (str[i] != MATCH_PAREN) {
            if (length > 0) {
                fix[fix_idx++] = length;
                length = 0;
            }
            if (str[i] == LEFT_PAREN) {
                fix[fix_idx++] = LEFT_PAREN_MARK;
            } else {
                fix[fix_idx++] = RIGHT_PAREN_MARK;
            }
        } else {
            length++;
        }
    }

    if (length > 0) {
        fix[fix_idx++] = length;
    }
#endif

    /* Check the substrings */
    int maxLength = 0;
    int prevSymbol = UNKNW_PAREN_MARK;

    for (int i=0; i<fix_idx; ++i) {
        int length = 0;
        int edits = K;

        if (prevSymbol != LEFT_PAREN_MARK &&
            prevSymbol != RIGHT_PAREN_MARK &&
            prevSymbol != UNKNW_PAREN_MARK) {
            /* Don't start analyzing when previous symbol
             * is not an unmatched parenthesis */
            prevSymbol = fix[i];
            continue;
        }
        prevSymbol = fix[i];

        int j = i;

        for (int prevBracket=0; j<fix_idx; ++j) {
            if (fix[j] != LEFT_PAREN_MARK &&
                fix[j] != RIGHT_PAREN_MARK) {
                length += fix[j];
                continue;
            }
            if (edits == 0) {
                break;
            }

            if (fix[j] == prevBracket) {
                length +=2;
                edits--;
                prevBracket = MATCH_PAREN_MARK;
            } else if (prevBracket == RIGHT_PAREN_MARK && fix[j] == LEFT_PAREN_MARK) {
                if (edits < 2) {
                    break;
                }
                length +=2;
                edits -= 2;
                prevBracket = MATCH_PAREN_MARK;
            } else {
                prevBracket = fix[j];
            }
        }

        if (length > maxLength) {
            maxLength = length;
        }

        /* If we've reached the last position no point
         * on continuing processing */
        if (j == fix_idx) {
            break;
        }
    }


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

    printf("%d\n", solution(S, K));
}
