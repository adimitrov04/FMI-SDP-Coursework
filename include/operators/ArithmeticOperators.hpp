#pragma once

#ifndef __ARITHMETICOPERATORS_HEADER_INCLUDED__
#define __ARITHMETICOPERATORS_HEADER_INCLUDED__

#include "Operator.h"
#include "OperatorSelector.hpp"

struct SumOperator : public Operator
{

public:
    SumOperator() : Operator('+', 2, 2) {}

public:
    int apply(const std::vector<int> &args) const override
    {
        int right = args[0];
        int left = args[1];

        return left + right;
    }

    bool isBracket () const override
    { return false; }
};
static OperatorRegistrator<SumOperator> _sumReg;

struct SubtractOperator : public Operator
{

public:
    SubtractOperator() : Operator('-', 1, 2)
    {}

public:
    int apply (const std::vector<int> &args) const override
    {
        int right = args[0];
        int left = args[1];

        return left - right;
    }

    bool isBracket () const override
    { return false; }
};
static OperatorRegistrator<SubtractOperator> _subReg;

struct MultiplyOperator : public Operator
{

public:
    MultiplyOperator () : Operator('*', 4, 2)
    {}

public:
    int apply (const std::vector<int> &args) const override
    {
        int right = args[0];
        int left = args[1];

        return left * right;
    }

    bool isBracket () const override
    { return false; }
};
static OperatorRegistrator<MultiplyOperator> _multReg;

struct DivideOperator : public Operator
{

public:
    DivideOperator () : Operator('/', 3, 2)
    {}

public:
    int apply (const std::vector<int> &args) const override
    {
        int right = args[0];
        int left = args[1];

        return left / right;
    }

    bool isBracket () const override
    { return false; }
};
static OperatorRegistrator<DivideOperator> _divReg;

struct NegativeOperator : public Operator
{

public:
    NegativeOperator () : Operator('_', 8, 1)
    {}

public:
    int apply (const std::vector<int> &args) const override
    {
        int arg = args[0];

        return -arg;
    }

    bool isBracket () const override
    { return false; }
};
static OperatorRegistrator<NegativeOperator> _negReg;

struct PowerOperator : public Operator
{

public:
    PowerOperator () : Operator('^', 7, 2)
    {}

public:
    int apply (const std::vector<int> &args) const override
    {
        int base = args[1], power = args[0];
        int result(1);

        if (power < 0)
            power *= -1;

        for (int i = 0; i < power; i++)
            result *= base;

        return (power * -1 < 0) ? result : (1 / result);
    }

    bool isBracket () const override
    { return false; }
};

static OperatorRegistrator<PowerOperator> _powReg;

#endif //__ARITHMETICOPERATORS_HEADER_INCLUDED__
