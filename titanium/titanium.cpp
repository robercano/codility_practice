#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <climits>

using namespace std;

#define DEBUG

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

void matchParenthesis(stack<char> &in_st, stack<int> &in_pos,
                      stack<char> &out_st, stack<int> &out_pos,
                      vector<int> &group, int maxMatches = INT_MAX)
{
    while (maxMatches > 0 && !in_st.empty()) {
#ifdef DEBUG
        cout << "Symbol: " << in_st.top() << endl;
#endif // DEBUG

        if (out_st.empty() == false && out_st.top() == '(' && in_st.top() == ')') {
            group[in_pos.top()] = 1;
            group[out_pos.top()] = 1;

            out_st.pop();
            out_pos.pop();

            maxMatches--;
        } else {
            out_st.push(in_st.top());
            out_pos.push(in_pos.top());
        }

        in_st.pop();
        in_pos.pop();

#ifdef DEBUG
        printStack("  In. Stack: ", in_st, false);
        printStack("  Out. Stack:", out_st, false);
        printStack("  In. Pos:   ", in_pos);
        printStack("  Out. Pos:  ", out_pos);
        printVector("  Group:", group);
#endif // DEBUG
    }
}

int solution(string &S, int K)
{
    stack<char> stA, stB;
    stack<int> posA, posB;
    vector<int> group;

    group.resize(S.length(), -1);

    /* Initialize input stack */
    for (int i = S.length()-1; i>=0; --i) {
        stA.push(S[i]);
        posA.push(i);
    }

    matchParenthesis(stA, posA, stB, posB, group);
#ifdef DEBUG
    cout << "Start fix" << endl << endl;
#endif // DEBUG
    matchParenthesis(stB, posB, stA, posA, group, K);

    int maxGroup = 0;
    int groupSize = 0;

    for (vector<int>::iterator it = group.begin(); it != group.end(); ++it) {
        if (*it == -1) {
            if (groupSize > maxGroup) {
                maxGroup = groupSize;
            }
            groupSize = 0;
        } else {
            groupSize++;
        }
    }
    if (groupSize > maxGroup) {
        maxGroup = groupSize;
    }

    return maxGroup;
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
