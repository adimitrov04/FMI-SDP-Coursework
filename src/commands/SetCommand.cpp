#include <new>
#include <cctype>
#include <stdexcept>

#include <tuple>

#include "../../include/commands/SetCommand.h"

#include "../../include/utils/ExpressionInterpreter.h"
#include "../../include/operators/AddressOperators.h"

SetCommand::SetCommand (std::vector<std::string> &setArgs)
: Command(setArgs)
{}

void SetCommand::Execute (Spreadsheet &sheet, std::istream &in, std::ostream &out)
{
    intp::cell_address add = intp::interpretAddress(args[0]);

    if (!add.row)
        throw std::logic_error("Invalid address.");

    int setRow(add.row), setCol(add.col);

    Spreadsheet::Iterator setCell = sheet.GetCell(setRow, setCol);
    sheet.SetCellValue(setCell, args[1]);

    AddressOperator::currentRow = setRow;
    AddressOperator::currentCol = setCol;
}

SetCommandGenerator::SetCommandGenerator ()
: CommandGenerator("SET", "SET <cell> <expression> - Sets the expression of the given cell.")
{}

Command *SetCommandGenerator::Generate (std::istream &in, std::ostream &out) const
{
    std::vector<std::string> outArgs;
    std::string address, expr;

    in >> address >> expr;
    outArgs.push_back(address);
    outArgs.push_back(expr);

    return new SetCommand(outArgs);
}