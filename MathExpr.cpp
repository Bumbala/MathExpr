/**
 * MathExpr is a command-line program to evaluate a simple mathematical expression.
 * Written by Tolga Akyay for SN Systems.
 */

#include <iostream>
#include <stack>
#include <deque>
#include <string>

using namespace std;

/**
 * Checks whether the specified character is a whitespace.
 * @param ch The character to check.
 * @returns true, if the character is whitespace, otherwise false.
 */
bool isWhitespace(const char ch)
{
    switch (ch)
    {
    case '\t':
    case ' ':
        return true;
    }

    return false;
}

/**
 * Checks whether the specified character is a number.
 * @param ch The character to check.
 * @returns true, if the character is a number, otherwise false.
 */
bool isNumber(const char ch)
{
    return isdigit(ch);
}

/**
 * Check whether the specified character is a mathematical operator.
 * @param ch The character to check.
 * @returns true, if the character is a maths operator, otherwise false.
 */
bool isOperator(const char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
    case '*':
    case '/':
        return true;
    }

    return false;
}

/**
 * Applies an operator to two given operands.
 * @param a First operand.
 * @param b Second operand.
 * @param op The operator.
 * @returns The result of the operation.
 */
int applyOperator(const int a, const int b, const char op)
{
    switch (op)
    {
    case '+':
        return a + b;

    case '-':
        return a - b;

    case '*':
        return a * b;

    case '/':
        return a / b;
    }

    // Should never get here.
    return 0;
}

/**
 * Parses and evaluates the given mathematical expression.
 * @param expression The expression as string to evaluate.
 * @param result The numerical result of the expression.
 * @returns true, if it was evaluated successfully, otherwise false.
 */
bool evaluate(const char* expression, int& result)
{
    // Stack to hold operands
    stack<int> operands;

    // Stack to hold operators
    stack<char> operators;

    string str(expression);
    const size_t len = str.length();

    int i, a, b;
    char ch, op;

    // Parse the expression in reverse order since there is no precedence.
    for (i = len - 1; i >= 0; i--)
    {
        ch = str[i];

        // Skip if the token is whitespace.
        if (isWhitespace(ch))
            continue;

        if (isNumber(ch))
        {
            // Parse the digits.
            string numStr(1, ch);
            int j;
            for (j = i - 1; j >= 0 && isNumber(str[j]); j--)
            {
                numStr.insert(0, 1, str[j]);
            }
            // The last character may be sign (+/-).
            if (j >= 0 && (str[j] == '+' || str[j] == '-'))
            {
                numStr.insert(0, 1, str[j]);
            }

            // Parse the operand and store it.
            int number = atoi(numStr.c_str());
            operands.push(number);

            i -= (numStr.length() - 1);
        }
        else if (isOperator(ch) || ch == ')')
        {
            operators.push(ch);
        }
        else if (ch == '(')
        {
            // Compute the parenthesis and store the result.
            while (!operators.empty() && operators.top() != ')')
            {
                if (operands.size() >= 2)
                {
                    // We should have at least a pair of operands.
                    if (operands.size() < 2)
                        return false;

                    a = operands.top();
                    operands.pop();

                    b = operands.top();
                    operands.pop();

                    op = operators.top();
                    operators.pop();

                    // Division by zero?
                    if (op == '/' && b == 0)
                        return false;

                    operands.push(applyOperator(a, b, op));
                }
                else
                {
                    // We have a single number inside parenthesis.
                    a = operands.top();
                    operands.pop();

                    operands.push(a);
                }
            }

            // Forgot to close the parenthesis.
            if (operators.empty())
                return false;

            // Pop the close parenthesis.
            operators.pop();
        }
        else
        {
            // Found an invalid character
            return false;
        }
    }

    // Number operands must be twice the number of operators.
    if (operands.size() != operators.size() * 2)
        return false;

    // Compute the result.
    while (!operators.empty())
    {
        op = operators.top();
        operators.pop();

        // We should have evaluated the brackets before.
        if (op == '(' || op == ')')
            return false;

        a = operands.top();
        operands.pop();

        b = operands.top();
        operands.pop();

        // Division by zero?
        if (op == '/' && b == 0)
            return false;

        operands.push(applyOperator(a, b, op));
    }

    // The result is at the top of the operand stack.
    result = operands.top();
    return true;
}

/**
 * Main entry point.
 */
int main()
{
    cout << "Please enter the expression or type \"exit\" to quit.\n";

    string expression;
    int result;
    while (true)
    {
        getline(cin, expression);

        if (strcmp("exit", expression.c_str()) == 0 ||
            strcmp("EXIT", expression.c_str()) == 0)
        {
            break;
        }

        result = 0;
        if (evaluate(expression.c_str(), result))
        {
            cout << result << "\n";
        }
        else
        {
            cout << "N/A\n";
        }
    }

    return 0;
}
