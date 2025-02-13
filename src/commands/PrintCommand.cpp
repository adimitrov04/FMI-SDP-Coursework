#include <iostream>

#include <new>
#include <cctype>
#include <stdexcept>

#include <utility>

#include "../../include/commands/PrintCommand.h"

#include "../../include/ExpressionInterpreter.h"
#include "../../include/operators/AddressOperators.h"

void PrintCommand::Execute (Spreadsheet &sheet, std::istream &in, std::ostream &out)
{
    if (args[0] == "EXPR")
    {
        if (args[1] == "ALL")
        {
            for (Spreadsheet::Iterator it = sheet.Begin(); it <= sheet.End(); it++)
            {
                out << it.data() << " | ";
                if (( it - sheet.Begin() + 1 ) % sheet.GetCols() == 0)
                    out << '\n';
            }
        }
        else
        {
            intp::cell_address add = intp::interpretAddress(args[1]);
            if (!add.row)
                throw std::logic_error("Invalid cell address.\n");

            int printRow(add.row), printCol(add.col);

            out << sheet.GetCell(printRow, printCol).data() << '\n';
            return;
        }
    }
    else if (args[0] == "VAL")
    {
        AddressOperator::connectedSheet = &sheet;
        int initialRow(AddressOperator::currentRow), initialCol(AddressOperator::currentCol);

        if (args[1] == "ALL")
        {
            AddressOperator::currentRow = 1;
            AddressOperator::currentCol = 1;

            for (Spreadsheet::Iterator it = sheet.Begin(); it <= sheet.End(); it++)
            {
                try
                {
                    out << intp::interpretExpression(it.data()) << " | ";
                }
                catch (std::logic_error&)
                {
                    out << "ERROR | ";
                }

                if (AddressOperator::currentCol == sheet.GetCols() - 1)
                {
                    AddressOperator::currentCol = sheet.GetCols();
                }
                else if (AddressOperator::currentCol == sheet.GetCols())
                {
                    AddressOperator::currentCol = 1;
                }
                else
                {
                    AddressOperator::currentCol++;
                }

                if (( it - sheet.Begin() + 1 ) % sheet.GetCols() == 0)
                {
                    AddressOperator::currentRow++;
                    out << '\n';
                }
            }
        }
        else
        {
            intp::cell_address add = intp::interpretAddress(args[1]);
            if (!add.row)
                throw std::logic_error("Invalid address.\n");

            int currentRow(add.col), currentCol(add.col);
            AddressOperator::currentRow = currentRow;
            AddressOperator::currentCol = currentCol;

            try
            {
                out << intp::interpretExpression(sheet.GetCell(currentRow, currentCol).data()) << "\n";
            }
            catch (std::logic_error&)
            {
                AddressOperator::currentRow = initialRow;
                AddressOperator::currentCol = initialCol;

                out << "ERROR\n";
            }

            AddressOperator::currentRow = initialRow;
            AddressOperator::currentCol = initialCol;

            return;
        }
    }
    else
    {
        throw std::logic_error("Invalid print mode.\n");
    }
}

Command *PrintCommandGenerator::Generate (std::istream &in, std::ostream &out) const
{
    std::vector<std::string> outArgs;
    std::string printMode, address;

    in >> printMode >> address;

    if (!in)
        throw std::runtime_error("Input failed. :(\n");

    outArgs.push_back(printMode);
    outArgs.push_back(address);

    return new PrintCommand(outArgs);
}