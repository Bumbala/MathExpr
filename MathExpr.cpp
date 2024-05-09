/**
 * MathExpr is a command-line program to evaluate a simple maths expression.
 * Written by Tolga Akyay for SN Systems
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

int evaluate(const deque<int>& operands, const deque<char>* operators)
{
    return 0;
}

/**
 * Parses and evaluates the given mathematical expression.
 * @param expression The expression as string to evaluate.
 * @param result The mathematical result of the expression.
 * @returns true, if it was evaluated successfully, otherwise false.
 */
bool evaluate(const char* expression, int& result)
{
    // Stack to hold operands
    stack<int> operands;

    // Stack to hold operators
    stack<char> operators;

    string str(expression);
    size_t len = str.length();

    // Parse the expression char by char.
    int i;
    for (i = 0; i < len; i++)
    {
        // Skip if the token is whitespace.
        if (isWhitespace(str[i]))
            continue;

        // Check for signed numbers as well.
        if (isNumber(str[i]) || ((str[i] == '+' || str[i] == '-') && i + 1 < len && isNumber(str[i + 1])))
        {
            // Count the number of digits.
            int count = 1;
            for (int j = i + 1; j < len && isNumber(str[j]); j++)
            {
                count++;
            }

            // Parse the operand and store it.
            int number = atoi(str.substr(i, count).c_str());
            operands.push(number);

            i += (count - 1);
        }
        else if (isOperator(str[i]) || str[i] == '(')
        {
            operators.push('(');
        }
        else if (str[i] == ')')
        {
            // Compute the parenthesis and store it.
            while (!operators.empty() && operators.top() != '(')
            {
                // We should have at least a pair of operands.
                if (operands.size() < 2)
                    return false;

                int b = operands.top();
                operands.pop();

                int a = operands.top();
                operands.pop();

                char op = operators.top();
                operators.pop();

                operands.push(applyOperator(a, b, op));
            }

            // Pop the opening parenthesis
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
        char op = operators.top();
        operators.pop();

        // We should have evaluated the brackets before.
        if (op == '(' || op == ')')
            return false;

        int b = operands.top();
        operands.pop();

        int a = operands.top();
        operands.pop();

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
