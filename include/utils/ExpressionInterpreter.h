#pragma once

#ifndef __EXPRESSIONINTERPRETER_HEADER_INCLUDED__
#define __EXPRESSIONINTERPRETER_HEADER_INCLUDED__

#include <string>

#include "linked_stack.hpp"

#include "../operators/Operator.h"
#include "../operators/OperatorSelector.hpp"

namespace intp
{

struct cell_address
{
    int row = 0, col = 0;
};

bool isCloseBracket (char c);

int getNumber (std::string::iterator &str);

char nearestChar (const std::string &str, std::string::iterator it, int direction);

std::vector<int> getArgs (const Operator* op, linked_stack<int> &args);

void applyTopOperator (linked_stack<const Operator*> &operators, linked_stack<int> &args);

// Shunting yard algorithm to interpret string expressions
int interpretExpression (std::string expr);

cell_address interpretAddress (std::string &str);

cell_address interpretAddress (std::string::iterator &it);

}

#endif //__EXPRESSIONINTERPRETER_HEADER_INCLUDED__
