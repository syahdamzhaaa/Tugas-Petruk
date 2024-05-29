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
  
    cetakToken(token);

    return 0;
}

