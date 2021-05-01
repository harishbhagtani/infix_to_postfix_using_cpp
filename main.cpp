/* Created By Harish Bhagtani on May 01, 2021
 * A C++ Program to Convert an Infix Expression to Post Fix
 * Read README file for the algorithm ()
 */
#include <iostream>
#include <ctype.h>

using namespace std;

//Ignore this stack class
class Stack {
public:

    //Max = 100
    static const int MAX = 100;
    char arr[MAX];
    int top = -1;

    int push(char element) {
        if (isFull()) {
            cout << "Overflow" << endl;
            return -1;
        }
        top++;
        arr[top] = element;
        return top;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Underflow" << endl;
            return -1;
        }
        int deletionElement = arr[top];
        top--;
        return deletionElement;
    }

    void printStack() {
        cout << "There are " << getCount() << " elements in stack." << endl;
        for (int i = 0; i <= top; i++) {
            cout << arr[i] << "\t";
        }
        cout << endl;
    }

    bool isEmpty() {
        return top < 0;
    }

    bool isFull() {
        return top >= 100;
    }

    char getTop() {
        return arr[top];
    }

    int getCount() {
        return top + 1;
    }
};

class InfixToPostfixUsingStack {

    const int RIGHT_ASSOCIATIVE = 1;
    const int LEFT_ASSOCIATIVE = 2;

    string infixExpression;
    string postFixExpression;

    int getPrecedence(char checkOperator) {
        if (checkOperator == '^' || checkOperator == '$') {
            return 3;
        } else if (checkOperator == '*' || checkOperator == '/') {
            return 2;
        } else if (checkOperator == '+' || checkOperator == '-') {
            return 1;
        } else {
            return -1;
        }
    }

    int getAssociativity(char checkOperator) {
        if (checkOperator == '^' || checkOperator == '$') {
            return RIGHT_ASSOCIATIVE;
        } else if (checkOperator == '+' || checkOperator == '-' || checkOperator == '/' || checkOperator == '*') {
            return LEFT_ASSOCIATIVE;
        }
    }

public:

    void setInfixExpression(string infixExpression) {
        this->infixExpression = infixExpression;
    }

    //Function to perform algorithm
    void convertInfixToPostFix() {

        Stack stack;

        for (int i = 0; i < infixExpression.length(); i++) {

            char currentSymbol = infixExpression[i];

            topOfTheLoop:

            //Case 1: For operands (which can be alphabets or numbers)
            if (isalpha(currentSymbol) || isnumber(currentSymbol)) {
                postFixExpression.push_back(currentSymbol);
                continue;
            }

            //Case 2: If Stack is empty
            if (stack.isEmpty()) {
                stack.push(currentSymbol);
                continue;
            }

            //Case 3: If we get "(" or ")"
            if (stack.getTop() == '(') {
                stack.push(currentSymbol);
                continue;
            } else if (currentSymbol == ')') {
                while (stack.getTop() != '(') {
                    postFixExpression.push_back(stack.pop());
                }
                stack.pop();
                continue;
            } else if (currentSymbol == '(') {
                stack.push(currentSymbol);
                continue;
            }

            //Case 4: If we get an operator, then we'll check precedence
            if (getPrecedence(stack.getTop()) < getPrecedence(currentSymbol)) {
                stack.push(currentSymbol);
            } else if (getPrecedence(stack.getTop()) == getPrecedence(currentSymbol)) {
                //if precedence is equal, we'll check associativity
                if (getAssociativity(currentSymbol) == RIGHT_ASSOCIATIVE) {
                    stack.push(currentSymbol);
                } else {
                    postFixExpression.push_back(stack.pop());
                    goto topOfTheLoop;
                }
            } else if (getPrecedence(stack.getTop()) > getPrecedence(currentSymbol)) {
                postFixExpression.push_back(stack.pop());
                goto topOfTheLoop;
            }
        }

        while (!stack.isEmpty()) {
            cout << endl;
            postFixExpression.push_back(stack.pop());
        }
    }

    void printPostFixExpression() {
        cout << "Infix: " << infixExpression << endl;
        cout << "Postfix: " << postFixExpression << endl;
    }
};


int main() {
    //Creating object of the class.
    InfixToPostfixUsingStack infixToPostfix;
    //Asking user to input infix expression
    infixToPostfix.setInfixExpression("2*3/(2-1)+5*(4-1)");
    //Converting Infix to Postfix
    infixToPostfix.convertInfixToPostFix();
    //Printing the post fix expression
    infixToPostfix.printPostFixExpression();
    return 0;
}
