#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <climits>

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

int main(int argc, char **argv)
{
    if (argc <= 2) {
        printf("Usage:\n\ttitanium \"<string>\" <K>\n\n<string> - List of parenthesis\n<K> - Max. number of swaps\n\n");
        return 1;
    }

    string S = argv[1];
    int K = strtol(argv[2], NULL, 0);

    printf("%d\n", solution(S, K));

    return 0;
}
