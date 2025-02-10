#include "../../include/commands/LoadCommand.h"

#include <fstream>

void LoadCommand::Execute (Spreadsheet &sheet, std::istream &in, std::ostream &out)
{
    std::ifstream file(args[0]);
    if (!file.is_open())
        throw std::logic_error("File does not exist or could not be accessed.\n");

    try
    {
        sheet.LoadFromFile(file);
    }
    catch (std::exception&)
    {
        file.close();
        throw;
    }

    file.close();
}

Command *LoadCommandGenerator::Generate (std::istream &in, std::ostream &out) const
{
    std::vector<std::string> outArgs;

    std::string filePath;
    in >> filePath;
    if (!in)
        throw std::logic_error("Invalid command syntax.\n");

    outArgs.push_back(filePath);

    return new LoadCommand(outArgs);
}