#pragma once

#ifndef __SAVECOMMAND_HEADER_INCLUDED__
#define __SAVECOMMAND_HEADER_INCLUDED__

#include "Command.h"

class SaveCommand : public Command
{

// Constructors
public:
    SaveCommand (std::vector<std::string> &setArgs);
    SaveCommand (const SaveCommand &other) = delete;

    ~SaveCommand () override = default;

// Operators
public:
    SaveCommand &operator= (const SaveCommand &other) = delete;

// Methods
public:
    void Execute (Spreadsheet &sheet, std::istream &in, std::ostream &out) override;

};

class SaveCommandGenerator : public CommandGenerator
{

public:
    SaveCommandGenerator();
    ~SaveCommandGenerator() override = default;

public:
    Command *Generate (std::istream &in, std::ostream &out) const override;

};

static SaveCommandGenerator _sReg;

#endif //__SAVECOMMAND_HEADER_INCLUDED__
