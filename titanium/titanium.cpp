#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <climits>
#include <sys/time.h>

using namespace std;

#define DEBUG
#define MEASURE_TIME

template<typename T>
void printStack(const string &text, const T *s, int size, bool reverse, bool showComma = true)
{
    cout << text << " [";
    if (reverse) {
        for (int i=size; i>=0; --i) {
            cout << s[i];
            if (showComma && i != 0) {
                cout << ",";
            }
        }
    } else {
        for (int i=0; i<size; ++i) {
            cout << s[i];
            if (showComma && i < size-1) {
                cout << ",";
            }
        }
    }
    cout << "]" << endl;
}

#define RIGHT_PAREN ')'
#define LEFT_PAREN  '('
#define MATCH_PAREN  '.'
#define UNKNW_PAREN  '*'

#define RIGHT_PAREN_MARK -2
#define LEFT_PAREN_MARK -1
#define MATCH_PAREN_MARK  1
#define UNKNW_PAREN_MARK 0

int solution(string &S, int K)
{

    int size = S.length();
    char st[size];
    int st_idx = -1;
    int pos[size];
    int pos_idx = -1;
    int fix[size];
    int fix_idx = 0;

#ifdef MEASURE_TIME
    struct timeval start, end;

    gettimeofday(&start, NULL);
#endif // MEASURE_TIME

    char *in = const_cast<char*>(S.c_str());

    for (int i=0; i<size; ++i) {
#ifdef DEBUG
        cout << "Symbol: " << in[i] << endl;
#endif // DEBUG
        if (st_idx >= 0 && st[st_idx] == LEFT_PAREN && in[i] == RIGHT_PAREN) {
            in[i] = in[pos[pos_idx]] = MATCH_PAREN;
            st_idx--;
            pos_idx--;
        } else {
            st[++st_idx] = in[i];
            pos[++pos_idx] = i;
        }
#ifdef DEBUG
        printStack("  Stack:", st, st_idx+1, true, false);
        printStack("  Pos:  ", pos, pos_idx+1, true);
        printStack("  String:", in, size, false, false);
#endif // DEBUG
    }
#ifdef MEASURE_TIME
    gettimeofday(&end, NULL);

    cout << "Time matching: " << ((end.tv_sec - start.tv_sec)*1000.0 + (end.tv_usec - start.tv_usec)/1000.0) << endl;

    gettimeofday(&start, NULL);
#endif // MEASURE_TIME

    int length = 0;
    size = S.length();

    for (int i=0; i<(int)S.length(); ++i) {
        if (S[i] != MATCH_PAREN) {
            if (length > 0) {
                fix[fix_idx++] = length;
                length = 0;
            }
            if (S[i] == LEFT_PAREN) {
                fix[fix_idx] = LEFT_PAREN_MARK;
            } else {
                fix[fix_idx] = RIGHT_PAREN_MARK;
            }
        } else {
            length++;
        }
    }
    if (length > 0) {
        fix[fix_idx++] = length;
    }

#ifdef MEASURE_TIME
    gettimeofday(&end, NULL);

    cout << "Time merging: " << ((end.tv_sec - start.tv_sec)*1000.0 + (end.tv_usec - start.tv_usec)/1000.0) << endl;

    gettimeofday(&start, NULL);
#endif // MEASURE_TIME
#ifdef DEBUG
    cout << "Start fix" << endl << "    ";

    for (int i=0; i<fix_idx; ++i) {
        cout << fix[i] << ",";
    }
    cout << endl;
#endif // DEBUG

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

#ifdef DEBUG
        cout << "Start substring at " << i << endl << "    ";
#endif // DEBUG

        int j = i;

        for (int prevBracket=0; j<size; ++j) {
            if (fix[j] != LEFT_PAREN_MARK &&
                fix[j] != RIGHT_PAREN_MARK) {
#ifdef DEBUG
                cout << ".";
#endif // DEBUG
                length += fix[j];
                continue;
            }
            if (edits == 0) {
                break;
            }

            if (fix[j] == prevBracket) {
#ifdef DEBUG
                if (fix[j] == RIGHT_PAREN_MARK) {
                    cout << ">";
                } else {
                    cout << "<";
                }
#endif // DEBUG
                length += 2;
                edits--;
                prevBracket = MATCH_PAREN_MARK;
            } else if (prevBracket == RIGHT_PAREN_MARK && fix[j] == LEFT_PAREN_MARK) {
                if (edits < 2) {
#ifdef DEBUG
                    cout << "(";
#endif // DEBUG
                    break;
                }
#ifdef DEBUG
                cout << "|";
#endif // DEBUG
                length +=2;
                edits -= 2;
                prevBracket = MATCH_PAREN_MARK;
            } else {
#ifdef DEBUG
                if (fix[j] == LEFT_PAREN_MARK) {
                    cout << "(";
                } else {
                    cout << ")";
                }
#endif // DEBUG
                prevBracket = fix[j];
            }
        }

#ifdef DEBUG
        cout << endl << "Length " << length << ", max " << maxLength << endl;
#endif // DEBUG

        if (length > maxLength) {
            maxLength = length;
        }

        /* If we've reached the last position no point
         * on continuing processing */
        if (j == fix_idx) {
            break;
        }
    }
#ifdef MEASURE_TIME
    gettimeofday(&end, NULL);

    cout << "Time fixing: " << ((end.tv_sec - start.tv_sec)*1000.0 + (end.tv_usec - start.tv_usec)/1000.0) << endl;
#endif // MEASURE_TIME

    return maxLength;
}

int main(int argc, char **argv)
{
#if 1
    if (argc <= 2) {
        printf("Usage:\n\ttitanium \"<string>\" <K>\n\n<string> - List of parenthesis\n<K> - Max. number of swaps\n\n");
        return 1;
    }

    string S = argv[1];
    int K = strtol(argv[2], NULL, 0);

    printf("%d\n", solution(S, K));
#else
    char *test = (char*)malloc(30000);
    if (test == NULL) {
        printf("ERROR allocating memory\n");
        exit(1);
    }

    srand(time(NULL));
    for (int i=0; i<30000; ++i) {
        test[i] = random()%2 ? '(' : ')';
    }
    string S = test;

    printf("%d\n", solution(S, 300000));
#endif
    return 0;
}
