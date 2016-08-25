#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <climits>
#include <unistd.h>

using namespace std;

//#define DEBUG

template<typename T>
void printStack(const string &text, const stack<T> &s, bool showComma = true)
{
    stack<T> reverse;
    for (stack<T> tmp = s; tmp.empty() == false; tmp.pop()) {
        reverse.push(tmp.top());
    }

    cout << text << " [";
    for (; reverse.empty() == false; reverse.pop()) {
        cout << reverse.top();
        if (showComma && reverse.size() != 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;
}

template<typename T>
void printVector(const string &text, const vector<T> &v, bool showComma = true)
{
    cout << text << " [";
    for (typename vector<T>::const_iterator it = v.begin(); it != v.end(); ++it) {
        cout << *it;
        if (showComma && (it - v.begin()) < v.size()-1) {
            cout << ",";
        }
    }
    cout << "]" << endl;
}

#define RIGHT_PAREN -1
#define LEFT_PAREN  -2
#define MATCH_PAREN  1
#define UNKNW_PAREN  0

int solution(string &S, int K)
{
    stack<char> st;
    stack<int> pos;
    vector<int> group;

    group.resize(S.length());

    for (int i=0; i<(int)S.length(); ++i) {
#ifdef DEBUG
        cout << "Symbol: " << S[i] << endl;
#endif // DEBUG
        if (st.empty() == false && st.top() == '(' && S[i] == ')') {
            group[i] = 1;
            group[pos.top()] = 1;

            st.pop();
            pos.pop();
        } else {
            group[i] = (S[i] == '(' ? LEFT_PAREN : RIGHT_PAREN);
            st.push(S[i]);
            pos.push(i);
        }
#ifdef DEBUG
        printStack("  Stack:", st, false);
        printStack("  Pos:  ", pos);
        printVector("  Group:", group);
#endif // DEBUG
    }

#ifdef DEBUG
    cout << "Start fix" << endl << "    " << endl;

    for (int i=0; i<(int)group.size(); ++i) {
        if (group[i] == 1) {
            cout << ".";
        } else if (group[i] == -1) {
            cout << ")";
        } else if (group[i] == -2) {
            cout << "(";
        }
    }
    cout << endl << endl;
#endif // DEBUG

    /* Check the substrings */
    int maxLength = 0;
    int prevSymbol = 0;

    for (int i=0; i<(int)group.size(); ++i) {
        int length = 0;
        int edits = K;

        if (prevSymbol == MATCH_PAREN) {
            /* Don't start analyzing when previous symbol
             * is not an unmatched parenthesis */
            prevSymbol = group[i];
            continue;
        }
        prevSymbol = group[i];

#ifdef DEBUG
        cout << "Start substring at " << i << endl << "    ";
#endif // DEBUG

        for (int j=i, prevBracket=0; j<(int)group.size(); ++j) {
            if (group[j] == MATCH_PAREN) {
#ifdef DEBUG
                cout << ".";
#endif // DEBUG
                length++;
                continue;
            }
            if (edits == 0) {
                break;
            }

            if (group[j] == prevBracket) {
#ifdef DEBUG
                if (group[j] == -1) {
                    cout << ">";
                } else {
                    cout << "<";
                }
#endif // DEBUG
                length +=2;
                edits--;
                prevBracket = MATCH_PAREN;
            } else if (prevBracket == RIGHT_PAREN && group[j] == LEFT_PAREN) {
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
                prevBracket = MATCH_PAREN;
            } else {
                prevBracket = group[j];
            }
        }

#ifdef DEBUG
        cout << endl << "Length " << length << ", max " << maxLength << endl;
#endif // DEBUG

        if (length > maxLength) {
            maxLength = length;
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
