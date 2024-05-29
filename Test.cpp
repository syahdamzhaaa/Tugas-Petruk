#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>
#include <stack>

using namespace std;

bool Operator(char karakter) {
    return karakter == '+' or karakter == '-' or karakter == '*' or karakter == '/' or 
                        karakter == '%' or karakter == '(' or karakter == ')';
}

bool Digit(char karakter) {
    return isdigit(karakter);
}

int Precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}

vector<string> tokenize(const string &infix) {
    vector<string> token;
    stringstream pengumpulString;
    bool sebelumnyaOperator = true;
    bool karakterPertama = true;

    for (size_t i = 0; i < infix.size(); ++i) {
        char karakter = infix[i];

        if (Digit(karakter)) {
            pengumpulString << karakter;
            sebelumnyaOperator = false;
            karakterPertama = false;
        } else if (Operator(karakter)) {
            if (pengumpulString.str().length() > 0) {
                token.push_back(pengumpulString.str());
                pengumpulString.str("");
            }

            if (karakter == '-' and (sebelumnyaOperator or (i > 0 && infix[i - 1] == '('))) {
                if (karakterPertama and i + 1 < infix.size() and infix[i + 1] == '(') {
                    token.push_back("-1");
                    token.push_back("*");
                } else if (karakterPertama) {
                    pengumpulString << karakter;
                    karakterPertama = false;
                } else {
                    token.push_back("-1");
                    token.push_back("*");
                }
            } else {
                token.push_back(string(1, karakter));
            }
            sebelumnyaOperator = (karakter != ')');
            karakterPertama = false;
        } else if (karakter == ' ') {
            if (pengumpulString.str().length() > 0) {
                token.push_back(pengumpulString.str());
                pengumpulString.str("");
            }
        }
    }
    if (pengumpulString.str().length() > 0) {
        token.push_back(pengumpulString.str());
    }
    return token;
}

vector<string> infixToPostfix(const vector<string> &infixTokens) {
    vector<string> postfix;
    stack<string> ops;

    for (const auto& token : infixTokens) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1]))) {
            postfix.push_back(token);
        } else if (token == "(") {
            ops.push(token);
        } else if (token == ")") {
            while (!ops.empty() && ops.top() != "(") {
                postfix.push_back(ops.top());
                ops.pop();
            }
            ops.pop();
        } else {
            while (!ops.empty() && Precedence(ops.top()[0]) >= Precedence(token[0])) {
                postfix.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
        }
    }

    while (!ops.empty()) {
        postfix.push_back(ops.top());
        ops.pop();
    }

    return postfix;
}

void cetakToken(const vector<string> &token) {
    for (size_t i = 0; i < token.size(); ++i) {
        if (i > 0) {
            cout << " ";
        }
        cout << token[i];
    }
    cout << "\n";
}

int main() {
    string infix;
    getline(cin, infix);

    vector<string> token = tokenize(infix);
    vector<string> postfix = infixToPostfix(token);
  
    cetakToken(token);

    return 0;
}

