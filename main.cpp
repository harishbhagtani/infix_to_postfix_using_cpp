/* Created By Harish Bhagtani on May 01, 2021
 * A C++ Program to Convert an Infix Expression to Post Fix
 * Read README file for the algorithm ()
 */

#include <iostream>
#include <ctype.h>
using namespace std;

//Implementing a char stack using array because
//we are going to use stack for conversion
class Stack{
public:

    //Max = 100
    static const int MAX = 100;
    char arr[MAX];
    int top = -1;

    int push(char element){
        if(isFull()){
            cout<<"Overflow"<<endl;
            return -1;
        }
        top++;
        arr[top] = element;
        return top;
    }

    int pop(){
        if(isEmpty()){
            cout<<"Underflow"<<endl;
            return -1;
        }
        int deletionElement = arr[top];
        top--;
        return deletionElement;
    }

    void printStack(){
        cout<<"There are "<<getCount()<<" elements in stack."<<endl;
        for(int i = 0;i <= top;i++){
            cout<<arr[i]<<"\t";
        }
        cout<<endl;
    }

    bool isEmpty(){
        return top < 0;
    }

    bool isFull(){
        return top >= 100;
    }

    char getTop(){
        return arr[top];
    }

    int getCount(){
        return top + 1;
    }
};

class InfixToPostfixUsingStack{

    const int RIGHT_ASSOCIATIVE = 1;
    const int LEFT_ASSOCIATIVE = 2;

    //String variable to store infix expression
    string infixExpression;

    //String variable to store post fix expression after evaluation
    string postFixExpression;

    /*
     * This function returns the precedence of an operator
     * 1. ^ & $ has the highest precedence (3)
     * 2. * & / has the second highest (2)
     * 3. + and - has the lowest precedence (1)
     * 4. If any other operator is being checked, return -1
     */

    int getPrecedence(char checkOperator){
        if(checkOperator == '^' || checkOperator == '$'){
            return 3;
        } else if (checkOperator == '*' || checkOperator == '/'){
            return 2;
        } else if (checkOperator == '+' || checkOperator == '-'){
            return 1;
        } else{
            return -1;
        }
    }

    /*
     * This function returns the associativity of the operator
     * 1. ^ and $ are right associative
     * 2. +,-,/ and * are left associative
     */

    int getAssociativity(char checkOperator){
        if(checkOperator == '^' || checkOperator == '$'){
            return RIGHT_ASSOCIATIVE;
        } else if(checkOperator == '+' || checkOperator == '-' || checkOperator == '/' || checkOperator == '*'){
            return LEFT_ASSOCIATIVE;
        }
    }

public:

    /*
     * This function takes the input from the user.
     */
    void getInfixExpressionFromUser(){
        cout<<"Please enter the infix expression: ";
        getline(cin>>ws, infixExpression);
    }

    /*
     * Function to manually set the value of infix expression;
     */

    void setInfixExpression(string infixExpression){
        this->infixExpression = infixExpression;
    }

    /*
     * This function performs the actual conversion from
     * Infix to Post fix of the given expression
     */

    void convertInfixToPostFix(){
        //Stack variable that going to be used in the conversion
        Stack stack;

        cout<<endl<<"Conversion Process Started, Scanning Symbols..."<<endl<<endl;

        /*
         * Scanning the infix string from left to right
         * Loop will go from 0 to length of string - 1
         */

        for(int i = 0;i < infixExpression.length();i++){
            //Variable to store current symbol
            char currentSymbol = infixExpression[i];
            topOfTheLoop:
            cout<<"Infix Expression: "<<infixExpression<<endl;
            cout<<"Current Symbol: "<<currentSymbol<<endl;

            /*
             * Checking current Symbol
             * Case 1: Symbol is alphabet (using isalpha() to check), then, insert into post fix directly
             * Case 2: Symbol is number (using isnumber() to check), then, insert into post fix directly
             * Case 3: Symbol is an operator, then follow the rules in algorithm
             */
            if(isalpha(currentSymbol) || isnumber(currentSymbol)){
                cout<<"Directly inserting to postfix because current symbol is alphabet..."<<endl;
                postFixExpression.push_back(currentSymbol);
            } else {

                //Rule 1: If stack is empty, directly insert the symbol
                if(stack.isEmpty()){
                    cout<<"Stack is empty. Pushing current symbol to stack."<<endl;
                    stack.push(currentSymbol);
                    goto endOfLoop;
                }
                if(stack.getTop() == '('){
                    //Rule 2: If top contains "(", push into stack.
                    cout<<"Top of stack is (, pushing symbol to stack."<<endl;
                    stack.push(currentSymbol);
                    goto endOfLoop;
                }else if(currentSymbol == ')'){

                    //Rule 3: If current symbol is ")", pop the stack and insert popped element
                    //to the postfix expression until "(" is found. After this, pop "(" also.

                    //Loop to pop all the elements from stack and inserting to postfix
                    //until "(" is found.
                    cout<<"Popping all the elements until \"(\"."<<endl;
                    while (stack.getTop() != '('){
                        postFixExpression.push_back(stack.pop());
                    }

                    //After the loop exits, we have "(" at the top of the stack
                    //At the end, deleting left parenthesis from the top of stack
                    stack.pop();
                    goto endOfLoop;

                } else if (currentSymbol == '('){
                    //Rule 6: If symbol is "(", always push it to stack.
                    cout<<"Inserting to stack."<<endl;
                    stack.push(currentSymbol);
                    goto endOfLoop;
                } else if (getPrecedence(stack.getTop()) < getPrecedence(currentSymbol)){
                    //Rule 4: If precedence of current symbol is higher than the top of stack, push.
                    cout<<"Precedence of "<<currentSymbol<<" is higher than top of stack("<<stack.getTop()<<"). Pushing to stack."<<endl;
                    stack.push(currentSymbol);
                } else if (getPrecedence(stack.getTop()) == getPrecedence(currentSymbol)){

                    //Rule 5: If precedence of current symbol is equal to top of stack, push only
                    //if the operator is right associative. Otherwise pop out element and insert
                    //it to post fix expression.

                    /*
                     * Checking the associativity
                     * If right associative, push into stack.
                     * If left associative, delete from stack and insert to post fix.
                     */
                    cout<<"Precedence of "<<currentSymbol<<" is equal to top of stack("<<stack.getTop()<<")";
                    if(getAssociativity(currentSymbol) == RIGHT_ASSOCIATIVE){
                        cout<<". Right Associative, pushing to stack."<<endl;
                        stack.push(currentSymbol);
                    }else{
                        cout<<". Left associative, popping and inserting to postfix"<<endl;
                        postFixExpression.push_back(stack.pop());
                        //Now scan the current symbol again the symbol again.
                        cout<<"Now we will evaluate same symbol again..."<<endl;
                        goto topOfTheLoop;
                    }
                } else if (getPrecedence(stack.getTop()) > getPrecedence(currentSymbol)){
                    cout<<"Precedence of "<<currentSymbol<<" is lower than top of stack("<<stack.getTop()<<")."<<endl;
                    cout<<"Popping top element and inserting to post fix... Then we'll evaluate current symbol again."<<endl;
                    postFixExpression.push_back(stack.pop());
                    goto topOfTheLoop;
                } else{
                    //In all the other cases, pop out the element from stack and insert it to post fix
                    if(stack.isEmpty()){
                        cout<<"Stack is empty"<<endl;
                    }else{
                        cout<<"Top of stack: "<<stack.getTop()<<endl;
                    }
                    cout<<"Popping and inserting to postfix..."<<endl;
                    postFixExpression.push_back(stack.pop());
                }
            }
            endOfLoop:
            cout<<endl<<"Stack State: "<<endl;
            stack.printStack();
            cout<<"Current State of Post Fix Expression: "<<postFixExpression<<endl<<endl;

            cout<<endl<<"--------------------------------------------------------"<<endl<<endl;
        }

        cout<<"Expression Full Scanned..."<<endl;
        stack.printStack();

        //After scanning each symbol, if stack is not empty.
        //Then popping elements from stack and inserting to postfix
        if(!stack.isEmpty()){
            cout<<"Popping remaining elements and inserting to post fix..."<<endl;
        }

        while(!stack.isEmpty()){
            cout<<endl;
            postFixExpression.push_back(stack.pop());
        }
    }

    /*
     * This function will print the post fix expression after conversion.
     */

    void printPostFixExpression(){
        cout<<endl<<endl;
        cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
        cout<<"The post fix expression at the end is: "<<postFixExpression<<endl;
        cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
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
