#include "../../include/commands/NewCommand.h"

#include <stdexcept>

#include "../../include/commands/CommandFactory.hpp"
#include "../../include/operators/AddressOperators.h"

NewCommand::NewCommand (std::vector<std::string> &setArgs)
: Command(setArgs)
{}

void NewCommand::Execute (Spreadsheet &sheet, std::istream &in, std::ostream &out)
{
    CommandFactory &thefac = CommandFactory::GetFactory();

    size_t setRows, setCols;
    setRows = std::stol(args[0]);
    setCols = std::stol(args[1]);

    out << "All unsaved changes to this sheet will be lost. Do you wish to save the current sheet? (y/n): ";

    char confirmation;
    in.ignore();
    in.get(confirmation);

    if (confirmation == 'y')
    {
        out << "Save to path: ";

        const CommandGenerator *saveGen = thefac.GetGenerator("SAVE");
        Command *cmd = saveGen->Generate(in, out);

        try
        {
            cmd->Execute(sheet, in, out);
        }
        catch (std::exception &e)
        {
            std::cout << saveGen->GetGeneratorID() << ": " << e.what();
            delete cmd;

            throw std::runtime_error("File saving failed. New sheet was not created.\n");
        }
    }
    else if (confirmation != 'n')
    {
        throw std::logic_error("Invalid command syntax.\n");
    }

    sheet.Clear();
    sheet.CreateNew(setRows, setCols);

    out << "Created a new sheet " << sheet.GetRows() << 'x' << sheet.GetCols() << '\n';
    AddressOperator::currentRow = 1;
    AddressOperator::currentCol = 1;
}

Command *NewCommandGenerator::Generate (std::istream &in, std::ostream &out) const
{
    size_t setRows, setCols;
    in >> setRows >> setCols;

    if (!in)
        throw std::logic_error("Invalid command syntax, type HELP for more info.\n");

    std::vector<std::string> outArgs;
    outArgs.push_back(std::to_string(setRows));
    outArgs.push_back(std::to_string(setCols));

    return new NewCommand(outArgs);
}