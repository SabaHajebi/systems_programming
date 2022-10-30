#include "infix.h"

int assignPrecedence(struct double_stack *this, char *ch)
{
	int operator1 = this->items[this->top - 1];
	if ((operator1 == '^' && ch[0] == '^') ||
		(operator1 == 'X' || operator1 == '/') && (ch[0] == 'X' || ch[0] == '/') ||
		(operator1 == '+' || operator1 == '-') && (ch[0] == '+' || ch[0] == '-') ||
		(operator1 > ch[0]))
		return 1;
	else
		return 0;
}

int isOperator(char *ch)
{
	if (strcmp(ch, "+") == 0 ||
		strcmp(ch, "-") == 0 ||
		strcmp(ch, "X") == 0 ||
		strcmp(ch, "/") == 0 ||
		strcmp(ch, "^") == 0)
		return 1;

	else
		return 0;
}

int isOperand(char *ch)
{
	if (ch[0] >= '0' && ch[0] <= '9')
		return 1;

	else
		return 0;
}

// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char **args, int nargs) {
	struct double_stack *stack = double_stack_new(nargs);
	char **postfix = malloc(nargs * sizeof(char *));
	char **infix = 0;
	infix = args;
	int postfixIndex = 0;
	int operator = 0;

	for (int i = 0; i < nargs; i++) {  							// if the value is an operand push it onto the postfix stack
		if (isOperand(infix[i])){
			postfix[postfixIndex] = infix[i];
			postfixIndex += 1;
		}

		else if (infix[i][0] == '(')						 	// if the value is the right bracket, push the index of it onto the stack
			double_stack_push(stack, i);

		else if (isOperator(infix[i]))							// if the value is an operator, deduce the precedence and push onto postfix stack
		{
			while (assignPrecedence(stack, infix[i]))
			{
				operator = double_stack_pop(stack);
				postfix[postfixIndex] = infix[operator];
				postfixIndex += 1;

			}
			double_stack_push(stack, i);
		}

		else if (infix[i][0] == ')')							
		{
			while (((stack->items[stack->top - 1]) != '(') && (stack->top > 0))
			{
				operator = double_stack_pop(stack);
				postfix[postfixIndex] = infix[operator];
				postfixIndex += 1;
			}
		}

	}
	do
	{
		operator = double_stack_pop(stack);						// continue popping and then evaulate newly formed postfix expression
		postfix[postfixIndex++] = infix[operator];
	} while (stack->top > 0);

		return evaluate_postfix_expression(postfix, postfixIndex);
}