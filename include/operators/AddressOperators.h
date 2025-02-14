#pragma once

#ifndef __ADDRESSOPERATORS_HEADER_INCLUDED__
#define __ADDRESSOPERATORS_HEADER_INCLUDED__

#include "Operator.h"
#include "OperatorSelector.hpp"

#include "../Spreadsheet.h"

#include "../utils/ExpressionInterpreter.h"

struct AddressOperator : public Operator
{
    AddressOperator(char s, int p, int argc) : Operator(s, p, argc) {}
    static Spreadsheet *connectedSheet;
    static int currentRow, currentCol;
};

struct AbsoluteAddressOperator : public AddressOperator
{

public:
    AbsoluteAddressOperator () : AddressOperator('R', 7, 2) {}

public:
    int apply (const std::vector<int> &args) const override
    {
        int row(args[1]), col(args[0]);

        if (row == currentRow && col == currentCol)
            throw std::logic_error("Invalid expression: infinite recursion in expression.\n");

        if (row <= 0 || row >= connectedSheet->GetRows()
            || col <= 0 || col >= connectedSheet->GetCols())
            throw std::logic_error("Invalid expression: invalid cell address.\n");

        std::string cellExpression = AddressOperator::connectedSheet->GetCell(row, col).data();

        return intp::interpretExpression(cellExpression);
    }

    bool isBracket () const override
    { return false; }

};
static OperatorRegistrator<AbsoluteAddressOperator> _absAdrReg;

struct RowOffsetOperator : public AddressOperator
{

public:
    RowOffsetOperator() : AddressOperator('r', 8, 1) {}

public:
    int apply (const std::vector<int> &args) const override
    {
        int offset = args[0];
        return currentRow + offset;
    }

    bool isBracket () const override
    { return false; }

};
static OperatorRegistrator<RowOffsetOperator> _rowOffReg;

struct ColOffsetOperator : public AddressOperator
{

public:
    ColOffsetOperator () : AddressOperator('c', 8, 1)
    {}

public:
    int apply (const std::vector<int> &args) const override
    {
        int offset = args[0];
        return currentCol + offset;
    }

    bool isBracket () const override
    { return false; }

};
static OperatorRegistrator<ColOffsetOperator> _colOffReg;

#endif //__ADDRESSOPERATORS_HEADER_INCLUDED__
