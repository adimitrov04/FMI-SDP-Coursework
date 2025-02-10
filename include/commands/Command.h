#pragma once

#ifndef __COMMAND_HEADER_INCLUDED__
#define __COMMAND_HEADER_INCLUDED__

#include <iostream>

#include <vector>
#include <string>

#include "../Spreadsheet.h"

class Command
{

// Constructors
public:
    Command (std::vector<std::string> &setArgs) : args(setArgs) {}
    Command (const Command &other) = delete;

    virtual ~Command () = default;

public:
    Command &operator= (const Command &other) = delete;

public:
    virtual void Execute (Spreadsheet &sheet, std::istream &in, std::ostream &out) = 0;

protected:
    std::vector<std::string> args;

};


class CommandGenerator
{

public:
    CommandGenerator (const char *setIdentifier, const char* setUsageInfo);
    virtual ~CommandGenerator () = default;

public:
    std::string GetGeneratorID () const
    { return identifier; }

    std::string GetCommandUsage () const
    { return usage_info; }

    virtual Command *Generate (std::istream &in, std::ostream &out) const = 0;

protected:
    std::string identifier, usage_info;

};

#endif //__COMMAND_HEADER_INCLUDED__
