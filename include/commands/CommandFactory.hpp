#pragma once

#ifndef __COMMANDFACTORY_HEADER_INCLUDED__
#define __COMMANDFACTORY_HEADER_INCLUDED__

#include <iostream>

#include <vector>
#include <string>

#include "Command.h"

class CommandFactory
{

// Constructors
public:
    static CommandFactory &GetFactory ()
    {
        static CommandFactory theFactory;
        return theFactory;
    }

    ~CommandFactory () = default;

// Operators
public:
    CommandFactory &operator= (const CommandFactory &other) = delete;

// Methods
public:
    Command *GenerateCommand (std::istream &in, std::ostream &out)
    {
        std::string commandName;
        in >> commandName;

        const CommandGenerator *gen = GetGenerator(commandName);
        if (!gen)
            return nullptr;

        return gen->Generate(in, out);
    }

    const CommandGenerator *GetGenerator (const std::string &generatorID)
    {
        for (size_t i = 0; i < commandBase.size(); i++)
        {
            if (commandBase[i]->GetGeneratorID() == generatorID)
                return commandBase[i];
        }

        return nullptr;
    }

    void RegisterCommand (const CommandGenerator *generator)
    {
        if (!generator || GetGenerator(generator->GetGeneratorID()))
            return;

        commandBase.push_back(generator);
    }

    void ListCommands (std::ostream &out) const
    {
        for (size_t i = 0; i < commandBase.size(); i++)
        {
            out << commandBase[i]->GetCommandUsage() << '\n';
        }
    }

private:
    CommandFactory () = default;
    CommandFactory (const CommandFactory &other) = delete;

// Members
private:
    std::vector<const CommandGenerator*> commandBase;

};


#endif //__COMMANDFACTORY_HEADER_INCLUDED__
