#pragma once

#ifndef __EXPRESSIONINTERPRETER_HEADER_INCLUDED__
#define __EXPRESSIONINTERPRETER_HEADER_INCLUDED__

#include <string>

#include "utils/linked_stack.hpp"

#include "operators/Operator.h"
#include "operators/OperatorSelector.hpp"

namespace intp
{

bool isCloseBracket (char c);

int getNumber (std::string::iterator &str);

char nearestChar (const std::string &str, std::string::iterator it, int direction);

std::vector<int> getArgs (const Operator* op, linked_stack<int> &args);

void applyTopOperator (linked_stack<const Operator*> &operators, linked_stack<int> &args);

// Shunting yard algorithm to interpret string expressions
int interpretExpression (std::string expr);

}

#endif //__EXPRESSIONINTERPRETER_HEADER_INCLUDED__
