#pragma once

#ifndef __NEWCOMMAND_HEADER_INCLUDED__
#define __NEWCOMMAND_HEADER_INCLUDED__

#include "Command.h"

class NewCommand : public Command
{

// Constructors
public:
    NewCommand (std::vector<std::string> &setArgs);
    NewCommand (const NewCommand &other) = delete;

    ~NewCommand () override = default;

// Operators
public:
    NewCommand &operator= (const NewCommand &other) = delete;

public:
    void Execute (Spreadsheet &sheet, std::istream &in, std::ostream &out) override;

};

class NewCommandGenerator : public CommandGenerator
{
public:
    NewCommandGenerator ()
    : CommandGenerator("NEW", "NEW <rows> <cols> - Create new empty sheet with the given dimensions.\n")
    {}

public:
    Command *Generate(std::istream &in, std::ostream &out) const override;

};
static NewCommandGenerator _nReg;

#endif //__NEWCOMMAND_HEADER_INCLUDED__
