#pragma once

#ifndef __SETCOMMAND_HEADER_INCLUDED__
#define __SETCOMMAND_HEADER_INCLUDED__

#include "Command.h"

class SetCommand : public Command
{

// Constructors
public:
    SetCommand (std::vector<std::string> &setArgs);
    SetCommand (const SetCommand &other) = delete;

    ~SetCommand () override = default;

// Operators
public:
    SetCommand &operator= (const SetCommand &other) = delete;

// Methods
public:
    void Execute (Spreadsheet &sheet, std::istream &in, std::ostream &out) override;

};

class SetCommandGenerator : public CommandGenerator
{

public:
    SetCommandGenerator ();
    ~SetCommandGenerator() override = default;

public:
    Command *Generate (std::istream &in, std::ostream &out) const override;

};

static SetCommandGenerator _sReg;

#endif //__SETCOMMAND_HEADER_INCLUDED__
