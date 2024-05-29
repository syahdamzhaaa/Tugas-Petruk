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

string infixToPostfix(const string& infix) {
    stringstream postfix;
    stack<char> operators;
    bool expectUnary = true;

    int n = infix.size();
    for (int i = 0; i < n; ++i) {
        if (isspace(infix[i])) 
            continue;

        if (isdigit(infix[i])) {
            postfix << infix[i];
            while (i + 1 < n && (isdigit(infix[i + 1]) || infix[i + 1] == '.')) {
                postfix << infix[++i];
            }
            postfix << ' ';
            expectUnary = false;
        } else if (infix[i] == '(') {
            operators.push('(');
            expectUnary = true;
        } else if (infix[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix << operators.top() << ' ';
                operators.pop();
            }
            operators.pop(); 
            expectUnary = false;
        } else if (Operator(infix[i])) {
            if (expectUnary && infix[i] == '-') {
                postfix << "-1 ";
                operators.push('*');
            } else {
                while (!operators.empty() && Precedence(operators.top()) >= Precedence(infix[i])) {
                    postfix << operators.top() << ' ';
                    operators.pop();
                }
                operators.push(infix[i]);
            }
            expectUnary = true;
        }
    }

    while (!operators.empty()) {
        postfix << operators.top() << ' ';
        operators.pop();
    }

    return postfix.str();
}

int evaluatePostfix(const string& postfix) {
    stack<int> operands;
    stringstream ss(postfix);
    string token;

    while (ss >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1]))) {
            operands.push(stoi(token));
        } else {
            int right = operands.top();
            operands.pop();
            int left = operands.top();
            operands.pop();

            if (token == "+") operands.push(left + right);
            else if (token == "-") operands.push(left - right);
            else if (token == "*") operands.push(left * right);
            else if (token == "/") operands.push(left / right);
            else if (token == "%") operands.push(left % right);
        }
    }

    return operands.top();
}

int main() {
    string infix;
    getline(cin, infix);

    string postfix = infixToPostfix(infix);
    int result = evaluatePostfix(postfix);
    cout << result << endl;

 return 0;
}
