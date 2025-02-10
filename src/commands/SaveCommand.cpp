#include "../../include/commands/SaveCommand.h"

#include <fstream>
#include <stdexcept>

// ----- CONSTRUCTORS ------

SaveCommand::SaveCommand (std::vector<std::string> &setArgs)
: Command(setArgs)
{}

SaveCommandGenerator::SaveCommandGenerator ()
: CommandGenerator("SAVE", "SAVE <file_path>")
{}

// -------- METHODS --------

void SaveCommand::Execute (Spreadsheet &sheet, std::istream &in, std::ostream &out)
{
    std::ofstream file(args[0]);
    if (!file)
        throw std::runtime_error("File could not be created.\n");

    sheet.Serialize(file);
    out << "File has been saved.\n";
}

Command *SaveCommandGenerator::Generate (std::istream &in, std::ostream &out) const
{
    std::string filePath;
    in >> filePath;
    if (!in)
        throw std::runtime_error("Input failed.\n");

    std::vector<std::string> outArgs;
    outArgs.push_back(filePath);

    return new SaveCommand(outArgs);
}