#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>
#include <cmath>
#include <unordered_map>

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%' || c == 'l' 
        || c == 'c' || c == 's' || c == 't' || c == 'g' || c == '#' || c == '!');
}

int getPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/' || op == '%') {
        return 2;
    }
    else if (op == '^') {
        return 3;
    }
    else if (op == 'l' || op == 'c' || op == 's' || op == 't' || op == 'g') {
        return 4;
    }
    else if (op == '#' || op == '!') {
        return 5;
    }
    return 0;
}

std::string infixToPostfix(const std::string& infix) {
    std::string postfix = "";
    std::stack<char> operatorStack;

    std::string number = "";
    for (char c : infix) {
        if (std::isdigit(c)) {
            number += c;
        }
        else {
            if (!number.empty()) {
                postfix += number + " ";
                number = "";
            }
            if (c == '(') {
                operatorStack.push(c);
            }
            else if (c == ')') {
                while (!operatorStack.empty() && operatorStack.top() != '(') {
                    postfix += operatorStack.top();
                    postfix += " ";
                    operatorStack.pop();
                }
                operatorStack.pop();
            }
            else if (isOperator(c)) {
                while (!operatorStack.empty() && getPrecedence(operatorStack.top()) >= getPrecedence(c)) {
                    postfix += operatorStack.top();
                    postfix += " ";
                    operatorStack.pop();
                }
                operatorStack.push(c);
            }
            else if (c == '!') {
                postfix += "! ";
            }
            else if (c != ' ') {
                throw std::invalid_argument("Invalid character in the expression");
            }
        }
    }

    if (!number.empty()) {
        postfix += number + " ";
    }

    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        postfix += " ";
        operatorStack.pop();
    }

    return postfix;
}

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int performOperation(char op, int operand1, int operand2 = 0) {
    if (op == '+') {
        return operand1 + operand2;
    }
    else if (op == '-') {
        return operand1 - operand2;
    }
    else if (op == '*') {
        return operand1 * operand2;
    }
    else if (op == '/') {
        if (operand2 == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return operand1 / operand2;
    }
    else if (op == '^') {
        return std::pow(operand1, operand2);
    }
    else if (op == '%') {
        return operand1 % operand2;
    }
    else if (op == 'l') {
        if (operand1 <= 0) {
            throw std::invalid_argument("Logarithm of a non-positive number");
        }
        return std::log(operand1);
    }
    else if (op == 'c') {
        return std::cos(operand1);
    }
    else if (op == 's') {
        return std::sin(operand1);
    }
    else if (op == 't') {
        return std::tan(operand1);
    }
    else if (op == 'g') {
        return 1 / std::tan(operand1);
    }
    else if (op == '#') {
        return operand1 * (-1);
    }
    else if (op == '!') {
        return factorial(operand1);
    }
    else {
        throw std::invalid_argument("Unknown operator");
    }
}

int evaluatePostfix(const std::string& expression) {
    std::stack<int> operandStack;
    std::string number = "";
    for (char c : expression) {
        if (isdigit(c)) {
            number += c;
        }
        else if (c == ' ' && !number.empty()) {
            operandStack.push(std::stoi(number));
            number = "";
        }
        else if (isOperator(c)) {
            if (c == 'l' || c == 'c' || c == 's' || c == 't' || c == 'g' || c == '#' || c == '!') {
                if (operandStack.empty()) {
                    throw std::invalid_argument("Invalid expression");
                }
                int operand = operandStack.top();
                operandStack.pop();
                int result = performOperation(c, operand);
                operandStack.push(result);
            }
            else {
            if (operandStack.size() < 2) {
                throw std::invalid_argument("Invalid expression");
            }
            int operand2 = operandStack.top();
            operandStack.pop();
            int operand1 = operandStack.top();
            operandStack.pop();
            int result = performOperation(c, operand1, operand2);
            operandStack.push(result);
            }
        }
    }

    if (!number.empty()) {
        operandStack.push(std::stoi(number));
    }

    if (operandStack.size() != 1) {
        throw std::invalid_argument("Invalid expression");
    }

    return operandStack.top();
}

int main() {
    std::string infixExpression = "4^2+c(45-20)+#2+3!";
    std::string postfixExpression = infixToPostfix(infixExpression);
    std::cout << "Postfix Expression: " << postfixExpression << std::endl;
    int result = evaluatePostfix(postfixExpression);
    std::cout << "Result: " << result << std::endl;
    return 0;
}