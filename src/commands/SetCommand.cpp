#include <new>
#include <cctype>
#include <stdexcept>

#include <tuple>

#include "../../include/commands/SetCommand.h"

#include "../../include/ExpressionInterpreter.h"
#include "../../include/operators/AddressOperators.h"

static std::tuple<bool, bool, int, int> isValidAddress (std::string &str)
{
    if (str.length() < 4 && str.length() > 8)
        return { false, false, 0, 0 };

    bool relative(false);
    int row(0), col(0);
    std::string::iterator it = str.begin();

    if (*it != 'R')
        return { false, false, 0, 0 };

    it++;

    if (*it == '[')
    {
        it++;

        if (*it == '-' && isdigit(*( it + 1 )))
        {
            it++;
            row = AddressOperator::currentRow - intp::getNumber(it);
        } else if (isdigit(*it))
        {
            row = AddressOperator::currentRow + intp::getNumber(it);
        } else
        {
            return { false, false, 0, 0 };
        }

        if (*it != ']')
            return { false, false, 0, 0 };

        relative = true;
        it++;
    } else if (isdigit(*it))
    {
        row = intp::getNumber(it);
    } else
    {
        return { false, false, 0, 0 };
    }

    if (*it != 'C')
        return { false, false, 0, 0 };

    it++;

    if (*it == '[')
    {
        it++;

        if (*it == '-' && isdigit(*( it + 1 )))
        {
            col = AddressOperator::currentCol - intp::getNumber(it);
        } else if (isdigit(*it))
        {
            col = AddressOperator::currentCol + intp::getNumber(it);
        } else
        {
            return { false, false, 0, 0 };
        }

        if (*it != ']')
            return { false, false, 0, 0 };

        relative = true;
        it++;
    } else if (isdigit(*it))
    {
        col = intp::getNumber(it);
    } else
    {
        return { false, false, 0, 0 };
    }

    return { true, relative, row, col };
}

SetCommand::SetCommand (std::vector<std::string> &setArgs)
: Command(setArgs)
{}

void SetCommand::Execute (Spreadsheet &sheet, std::istream &in, std::ostream &out)
{
    std::tuple<bool, bool, int, int> add = isValidAddress(args[0]);

    if (!std::get<0>(add))
        throw std::logic_error("Invalid address.");

    int setRow = std::get<2>(add);
    int setCol = std::get<3>(add);

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