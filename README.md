# MathExpr
This is an application written by Tolga Akyay for SN Systems. The program
parses a mathematical expression from standard input and evaluates the
numerical result. If the expression can't be parsed N/A is returned.

## Installation
The program is written originally by Visual Studio 2019 (C++ 14).
You can open the solution in Visual Studio and compile it, or you
can use your favourite C++ compiler to build MathExpr.cpp.

## Usage
Launch the program and type your expression and hit "ENTER".
You can type "exit" to quit the program.

## Notes
The program does not take the multiplication and division precedence into account
since it was not asked in the assignment. The expression is parsed left-to-right.
Therefore, the following:

2 + 3 * 5

will yield 5 * 5 = 25.

Allow spaces between numbers and operators since the program tries to parse
numbers with signs as well. Alternatively if you strictly don't want to use
space you can write:

1+(-5)

which will yield -4.
