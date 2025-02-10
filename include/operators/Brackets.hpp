#pragma once

#ifndef __BRACKETS_HEADER_INCLUDED__
#define __BRACKETS_HEADER_INCLUDED__

#include <stdexcept>

#include "Operator.h"
#include "OperatorSelector.hpp"

struct BracketOperator : public Operator
{

public:
    BracketOperator (char s) : Operator(s, 0, 0) {}

public:
    int apply (const std::vector<int> &args) const override
    { throw std::logic_error("Invalid expression.\n"); }

    bool isBracket () const override
    { return true; }

    virtual bool isOpen () const = 0;

    virtual bool match (const char c) const = 0;
};

struct OpenBracketOperator : public BracketOperator
{

public:
    OpenBracketOperator () : BracketOperator('(')
    {}

public:
    bool isOpen () const override
    { return true; }

    bool match (const char c) const override
    { return c == ')'; }

};
static OperatorRegistrator<OpenBracketOperator> _opBrReg;

struct CloseBracketOperator : public BracketOperator
{

public:
    CloseBracketOperator () : BracketOperator(')')
    {}

public:
    bool isOpen () const override
    { return false; }

    bool match (const char c) const override
    { return c == '('; }

};
static OperatorRegistrator<CloseBracketOperator> _clBrReg;

#endif //__BRACKETS_HEADER_INCLUDED__
