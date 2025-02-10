#include <iostream>
#include <fstream>

#include <string>

#include "include/Spreadsheet.h"
#include "include/ExpressionInterpreter.h"

#include "include/commands/CommandFactory.hpp"
#include "include/commands/PrintCommand.h"
#include "include/operators/AddressOperators.h"

const int DEFAULT_SIZE = 100;

int main ()
{
    Spreadsheet sheet(DEFAULT_SIZE, DEFAULT_SIZE);
    CommandFactory &thefac = CommandFactory::GetFactory();

    AddressOperator::currentRow = 1;
    AddressOperator::currentCol = 1;

    std::string input;

    while (input != "EXIT")
    {
        std::cin >> input;
        if (input == "EXIT")
            break;

        if (input == "HELP")
        {
            std::cout << "Command list:\n";
            thefac.ListCommands(std::cout);
            continue;
        }

        const CommandGenerator *gen = thefac.GetGenerator(input);
        if (!gen)
        {
            std::cerr << "Unknown command, type HELP for the list of supported commands.\n";
            continue;
        }


        Command *cmd = gen->Generate(std::cin, std::cout);
        if (!cmd)
        {
            std::cerr << "Invalid command syntax for" << gen->GetGeneratorID() <<
            ", type HELP for the list of supported commands.\n";
            continue;
        }

        try
        {
            cmd->Execute(sheet, std::cin, std::cout);
        }
        catch (std::exception &e)
        {
            std::cout << gen->GetGeneratorID() << ": " << e.what();
        }

        delete cmd;
    }

    return 0;
}
