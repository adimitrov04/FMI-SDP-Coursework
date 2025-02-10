#include <cstring>

#include "../include/ExpressionInterpreter.h"

#include "../include/operators/Brackets.hpp"
#include "../include/operators/ArithmeticOperators.hpp"
#include "../include/operators/AddressOperators.h"

bool intp::isCloseBracket (char c)
{
    return c == ')' || c == ']';
}

int intp::getNumber (std::string::iterator &str)
{
    int result(0);

    while (*str && isdigit(*str))
    {
        result = ( result * 10 ) + ( *str - '0' );
        str++;
    }

    return result;
}

char intp::nearestChar (const std::string &str, std::string::iterator it, int direction)
{
    ( direction > 0 )? it++ : it--;

    while (it >= str.begin() && *it)
    {
        if (!isspace(*it))
            return *it;

        ( direction > 0 )? it++ : it--;
    }

    return '\0';
}

std::vector<int> intp::getArgs (const Operator *op, linked_stack<int> &args)
{
    std::vector<int> output;
    output.reserve(op->argc);

    for (short i = 0; i < output.capacity(); i++)
        output.push_back(args.pop());

    return output;
}

void intp::applyTopOperator (linked_stack<const Operator *> &operators, linked_stack<int> &args)
{
    std::vector<int> operatorArgs;

    try
    {
        operatorArgs = getArgs(operators.top(), args);
    } catch (std::underflow_error &)
    {
        throw std::logic_error("Invalid expression.\n");
    }

    args.push(operators.pop()->apply(operatorArgs));
}

// Shunting yard algorithm to interpret string expressions
int intp::interpretExpression (std::string expr)
{
    linked_stack<int> numbers;
    linked_stack<const Operator *> operators;
    std::string::iterator it = expr.begin();

    while (*it)
    {
        if (isspace(*it) || *it == 'C' || *it == ']')
        {
            it++;
            continue;
        }

        if (isdigit(*it))
        {
            numbers.push(getNumber(it));
            continue;
        }

        if (*it == '-')
        {
            char ident = nearestChar(expr, it, -1);

            if (!isdigit(ident) && !isCloseBracket(ident))
                *it = '_';
        }

        if (*it == 'R')
            *it = '&';

        if (*it == '[')
        {
            if (it > expr.begin() && *(it - 1) == '&')
            { *it = 'r'; }
            else if (it > expr.begin() && *(it - 1) == 'C')
            { *it = 'c'; }
            else
            { throw std::logic_error("Invalid expression.\n"); }
        }

        const Operator *op = OperatorSelector::GetSelector().SelectOperator(*it);
        if (!op)
            throw std::logic_error("Invalid expression.\n");

        if (op->isBracket())
        {
            const BracketOperator *bracket = dynamic_cast<const BracketOperator *>(op);

            // Check bracket matching
            if (bracket->isOpen())
            {
                operators.push(bracket);
            } else
            {
                while (!operators.is_empty() && !operators.top()->isBracket())
                {
                    applyTopOperator(operators, numbers);
                }

                if (operators.is_empty())
                    throw std::logic_error("Invalid expression, missing open bracket.\n");

                if (!dynamic_cast<const BracketOperator *>(operators.top())->match(bracket->symbol))
                    throw std::logic_error("Invalid expression, missing open bracket.\n");

                operators.pop();
            }

            it++;
            continue;
        }

        while (!operators.is_empty() && operators.top()->priority >= op->priority)
        {
            applyTopOperator(operators, numbers);
        }

        operators.push(op);
        it++;
    }

    while (!operators.is_empty())
    {
        applyTopOperator(operators, numbers);
    }

    int result(0);

    try
    {
        result = numbers.pop();
    } catch (std::underflow_error &)
    {
        throw std::logic_error("Invalid expression.\n");
    }

    if (!numbers.is_empty())
        throw std::logic_error("Invalid expression.\n");

    return result;
}