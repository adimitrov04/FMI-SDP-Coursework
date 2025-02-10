#pragma once

#ifndef __PRINTCOMMAND_HEADER_INCLUDED__
#define __PRINTCOMMAND_HEADER_INCLUDED__

#include "Command.h"

class PrintCommand : public Command
{

// Constructors
public:
    PrintCommand (std::vector<std::string> &setArgs)
    : Command(setArgs)
    {}

    PrintCommand (const PrintCommand &other) = delete;

    ~PrintCommand () override = default;

// Operators
public:
    PrintCommand &operator= (const PrintCommand &other) = delete;

// Methods
public:
    void Execute (Spreadsheet &sheet, std::istream &in, std::ostream &out) override;

};

class PrintCommandGenerator : public CommandGenerator
{

public:
    PrintCommandGenerator ()
    : CommandGenerator("PRINT", "PRINT <mode: VAL | EXPR> <cell | ALL> - Displays either the expression at the given cells (or all cells, in order) or the value of that expression.")
    {}

    ~PrintCommandGenerator () override = default;

public:
    Command *Generate (std::istream &in, std::ostream &out) const override;

};

static PrintCommandGenerator _pReg;

#endif //__PRINTCOMMAND_HEADER_INCLUDED__
