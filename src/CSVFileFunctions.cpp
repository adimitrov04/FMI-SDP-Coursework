#include "../include/utils/CSVFileFunctions.h"

#include <stdexcept>

static const size_t MAX_BUFFER_LEN = static_cast<size_t>(-1);

void csv::skip_cell (std::ifstream &file) noexcept
{
    while (!file.eof())
    {
        char current;
        file.get(current);

        if (current == '\"')
            break;
    }
}

void csv::analyze_file (std::ifstream &file, size_t &outRows, size_t &outCols, size_t &outFullCount)
{
    while (!file.eof())
    {
        char current;
        file.get(current);

        if (current == '\"')
        {
            skip_cell(file);
            outFullCount++;
        }
        else if (current == ';')
        {
            outCols++;
        }
        else if (current == '\n')
        {
            outRows++;
        }
        else if (current != '\r')
        {
            throw std::invalid_argument("Given file is not in CSV format.\n");
        }
    }

    outRows++;
    outCols /= outRows;
}

void csv::read_cell (std::string &dest, std::ifstream &file)
{
    std::getline(file, dest, '\"');
}