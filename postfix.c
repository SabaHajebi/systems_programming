#include "postfix.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char **args, int nargs)
{
	double num1;
	double num2;
	double result;
	struct double_stack *stack = double_stack_new(nargs);
	for (int i = 0; i < nargs; i++)
	{
		char x = args[i][0];
		char y = args[i][1];
		if ((x == '+' || x == '-' ||  x == '/' ||  x == 'X' ||  x == '^' ) && (y >= '0' && y <= '9')) //signed number
			double_stack_push(stack, atoi(args[i]));
		else if (x >= '0' && x <= '9')
			double_stack_push(stack, atoi(args[i])); //not signed

		else
		{
			num2 = double_stack_pop(stack);
			num1 = double_stack_pop(stack);

			switch (x)
			{
			case '+':
				result = num1 + num2;
				break;
			case '-':
				result = num1 - num2;
				break;
			case 'X':
				result = num1 * num2;
				break;
			case '/':
				result = num1 / num2;
				break;
			case '^':
				result = pow(num1, num2);
				break;
			}
			double_stack_push(stack, result);
		}
	}

	return double_stack_pop(stack);
}
