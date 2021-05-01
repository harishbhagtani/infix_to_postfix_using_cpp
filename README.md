Infix Expressions - Human Readable
Ex - 12 + (9 * 3) + 5^2 OR (P * R * T) / 100

Postfix Expression - The expressions computer use to evaluate internally
Ex- PR*T*100/

Algorithm (Using Stack)

Step 1: Take an infix expression as an input from the user.

Step 2: Scan the infix expression from left to right.

Step 3: If scanned character is an operand, output it.

Else, if the scanned character is operator, perform the following steps:

Step 4: In stack, we perform push() in the following cases:
    1. When stack is empty. 
    2. When the top of the stack is left parenthesis ("(").
    3. When the top of the stack contains lower precedence operator. 
    4. When the top of the stack contains equal precedence. (Only when the operator is right associative)
    5. When the symbol is left parenthesis("(").

Step 5: Pop in all the other cases.    
