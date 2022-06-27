#include <iostream>
#include <string>

using namespace std;

#define MAX_SIZE 100
char stack[MAX_SIZE];
int top = -1;

//WHEN STACK IS FULL
bool _isFull() {
    if (top == MAX_SIZE) 
        return true;
    else 
        return false;
}

//WHEN STACK IS EMPTY
bool _isEmpty() {
    if (top == -1) 
        return true;
    else 
        return false;
}
//PUSH FUNC
void _push(char item) {
    //WHEN STACK IS FULL
    if (_isFull()) {
        cout << "Stack is Full" << endl;
        return;
    }
    //WHEN STACK IS NOT FULL
    stack[++top] = item;
}
//POP FUNC
char _pop() {
    //WHEN STACK IS EMPTY
    if (_isEmpty()) {
        cout << "Stack is Empty" << endl;
        return -1;
    }
    //WHEN STACK IS NOT EMPTY
    return stack[top--];
}
//CALCULATE OPERATOR PRIORITY
int _compare(char item) {
    if (item == '+' || item == '-')
        return 1;
    else if (item == '*' || item == '/')
        return 2;
    else  
        return -1;
}

//CONVERT infix TO postfix
void infixToPostfix(string infix) {
    string result;
    int lparen = 0;
    int rparen = 0;

    //DO WHILE infixs' length
    for (int i = 0; i < infix.length(); i++) {
        //WHEN MINUS NUMBER IS INPUTED
        if (infix[0] == '-' && i == 0) {
            result += '-';
            continue;
        }
        //WHEN POSITIVE NUMBER IS INPUTED
        else if (infix[0] == '+' && i == 0) {
            continue;
        }
        //NUMBER INPUTED
        else if (infix[i] >= '0' && infix[i] <= '9') {
            result += infix[i];
        }
        //WHEN OPEN BRACKET INPUTED
        else if (infix[i] == '(') {
            lparen++;
            _push(infix[i]);
            //REPRESENT POSITIVE NEGATIVE NUMBER
            if (infix[i + 1] == '-') {
                i++;
                result += infix[i];
            }
            else if (infix[i + 1] == '+') {
                i++;
            }
        }
        //WHEN CLOSE BRACKET INPUTED
        else if (infix[i] == ')') {
            rparen++;
            //ADD RESULT BEFORE FIND ( IN STACK
            while (stack[top] != '(' && top != -1) {
                char oper = stack[top];
                _pop();
                result = result + " " + oper;
            }
            // POP (
            if (stack[top] == '(') {
                _pop();
            }
        }
        //COMPARE OPERATOR
        else if (infix[i] == '*' || infix[i] == '/' || infix[i] == '+'
            || infix[i] == '-') {
            //COMPARE OPERATOR WHICH IS IN STACK AND infix[i] PRRIORITY
            while (top != -1 && _compare(infix[i]) <= _compare(stack[top])) {
                //POP OPERATOR IN STACK
                result = result + " " + _pop();
            }
            result += " ";
            //PUSH infix[i]
            _push(infix[i]);
            //REPRESENT POSTIVIE NEGATIVE NUMBER
            if (infix[i + 1] == '-') {
                i++;
                result += infix[i];
            }
            else if (infix[i + 1] == '+') {
                i++;
            }
        }
        //EXCEPTRION
        else {
            cout << infix[i] << " is not proper operation\n";
            exit(1);
        }
    }
    //NOT PROPER BRACKET USE
    if (lparen != rparen) {
        cout << "it's not proper bracket use\n";
        exit(1);
    }
    //POP ALL OPERATOR IN STACK
    while (top != -1) {
        result = result + " " + _pop();
    }
    cout << result << endl;
}
//MAIN_FUNC
int main() {
    string infix;
    cout << "input infix >> ";
    getline(cin, infix, '\n');
    //WHILE infix is not ""
    while (infix != "") {
        infixToPostfix(infix);
        cout << endl;
        cout << "input infix >> ";
        getline(cin, infix, '\n');
    }
    return 0;
}
