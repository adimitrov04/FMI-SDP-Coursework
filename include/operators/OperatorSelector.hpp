#pragma once

#ifndef __OPERATORSELECTOR_HEADER_INCLUDED__
#define __OPERATORSELECTOR_HEADER_INCLUDED__

#include <vector>

#include "Operator.h"

class OperatorSelector
{

// Constructors
public:
    ~OperatorSelector () = default;

// Methods
public:
    static OperatorSelector &GetSelector ()
    {
        static OperatorSelector theSelector;
        return theSelector;
    }

    const Operator *SelectOperator (const char symbol)
    {
        for (size_t i = 0; i < operatorList.size(); i++)
        {
            if (operatorList[i]->symbol == symbol)
                return operatorList[i];
        }

        return nullptr;
    }

    void RegisterOperator (const Operator *op)
    {
        if (op && !SelectOperator(op->symbol))
            operatorList.push_back(op);
    }

// Members
private:
    std::vector<const Operator*> operatorList;

// Unavailable methods for a singleton
private:
    OperatorSelector () = default;
    OperatorSelector (const OperatorSelector &other) = delete;
    OperatorSelector &operator= (const OperatorSelector &other) = delete;

};

template <class OP>
class OperatorRegistrator
{

public:
    OperatorRegistrator()
    { OperatorSelector::GetSelector().RegisterOperator(&op); }

private:
    OP op;

};

#endif //__OPERATORSELECTOR_HEADER_INCLUDED__
