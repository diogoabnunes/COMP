/*Without a scanner or parser generator,
implement a scanner for a language with the following tokens:
    LPAR=“(“
    RPAR=“)”
    MUL=“*”
    DIV=“\”
    PLUS=“+”
    SUB=“-”
    INT=[0-9]+
    VAR=[A-Za-z][0-9A-Za-z]*
    EQ=“=“
    SMICOLON=“;”

The scanner shall receive as input 
a string or a file and shall output the sequence of tokens 
in the input or shall report possible errors!

Note: skip the symbol: “\n”, “\r”, “ “, “\t”*/

//------------------------------------------------------------

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

#define INITIAL_STATE 0
#define INT_STATE 1
#define VAR_STATE 2
#define ERROR -1

int updateString(vector<string> &ret, char ch) {
    if (ch == '\n' || ch == '\r' || ch == ' ' || ch == '\t') return 0;

    switch(ch) {
        case '(': ret.push_back("LPAR"); break;
        case ')': ret.push_back("RPAR"); break;
        case '*': ret.push_back("MUL"); break;
        case '+': ret.push_back("SUM"); break;
        case '-': ret.push_back("SUB"); break;
        case '/': ret.push_back("DIV"); break;
        case '=': ret.push_back("EQ"); break;
        case ';': ret.push_back("SMICOLON"); break;

        default: cout << "Unknown character: " << ch << endl; return ERROR;
    }
    return 0;
}

int parseChar(vector<string> &ret, char ch, int &state) {
    switch(state) {

        case INITIAL_STATE:
            if (isdigit(ch)) {
                state = INT_STATE;
                ret.push_back("INT");
            }
            else if (isalpha(ch)) {
                state = VAR_STATE;
                ret.push_back("VAR");
            }
            else if (updateString(ret, ch) == ERROR) return ERROR;
            break;

        case INT_STATE:
            if (!isdigit(ch)) {
                state = INITIAL_STATE;
                if (updateString(ret, ch) == ERROR) return ERROR;
            }
            break;

        case VAR_STATE:
            if (!isalpha(ch) && !isdigit(ch)) {
                state = INITIAL_STATE;
                if (updateString(ret, ch) == ERROR) return ERROR;
            }
            break;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    vector<string> ret;
    char ch;
    int state = INITIAL_STATE;
    string input = argv[1];

    for (int i = 0; i < input.size(); i++) {
        ch = input[i];
        if (parseChar(ret, ch, state) == ERROR) return 1;
    }

    cout << "String: " << input << endl;
    cout << "Scanner: "; for (int i = 0; i < ret.size(); i++) cout << ret[i] << " "; cout << endl;

    return 0;
}