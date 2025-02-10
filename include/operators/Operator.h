#pragma once

#ifndef __OPERATOR_HEADER_INCLUDED__
#define __OPERATOR_HEADER_INCLUDED__

#include <vector>

struct Operator
{

public:
    virtual ~Operator () = default;

public:
    virtual int apply(const std::vector<int> &args) const = 0;
    virtual bool isBracket() const = 0;

protected:
    Operator(char setSymbol, short setPriority, short setArgCount)
    : symbol(setSymbol)
    , priority(setPriority)
    , argc(setArgCount)
    {}

public:
    char symbol;
    short priority, argc;

private:
    Operator() : symbol('\0'), priority(0), argc(0) {}

};


#endif //__OPERATOR_HEADER_INCLUDED__
