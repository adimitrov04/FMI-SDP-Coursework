#pragma once

#ifndef __LOADCOMMAND_HEADER_INCLUDED__
#define __LOADCOMMAND_HEADER_INCLUDED__

#include "Command.h"

class LoadCommand : public Command
{

// Constructors
public:
    LoadCommand (std::vector<std::string> &setArgs) : Command(setArgs) {}
    LoadCommand (const LoadCommand &other) = delete;

    ~LoadCommand () override = default;

// Operators
public:
    LoadCommand &operator= (const LoadCommand &other) = delete;

// Methods
public:
    void Execute (Spreadsheet &sheet, std::istream &in, std::ostream &out) override;

// Members
private:


};

class LoadCommandGenerator : public CommandGenerator
{

public:
    LoadCommandGenerator ()
    : CommandGenerator("LOAD", "LOAD <file_path>")
    {}

    ~LoadCommandGenerator () override = default;

public:
    Command *Generate (std::istream &in, std::ostream &out) const override;

};

static LoadCommandGenerator _lReg;

#endif //__LOADCOMMAND_HEADER_INCLUDED__
