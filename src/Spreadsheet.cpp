#include "../include/Spreadsheet.h"
#include "../include/utils/CSVFileFunctions.h"

#include <new>
#include <stdexcept>

using Iterator = Spreadsheet::Iterator;

// ----- CONSTRUCTORS ------

Spreadsheet::Spreadsheet (int setRows, int setCols)
{
    data = new node[setRows * setCols];

    for (size_t i = 0; i < setRows * setCols; i++)
        data[i] = nullptr;

    rows = setRows;
    cols = setCols;
}

Spreadsheet::Spreadsheet (std::ifstream &file)
: Spreadsheet()
{
    LoadFromFile(file);
}

Spreadsheet::~Spreadsheet ()
{ Clear(); }

// ------- OPERATORS -------

// -------- METHODS --------

void Spreadsheet::CreateNew (size_t setRows, size_t setCols)
{
    if (data)
        throw std::logic_error("Cannot create new when current table is not empty.\n");

    data = new node[setRows * setCols];
    rows = setRows;
    cols = setCols;

    for (size_t i = 0; i < rows * cols; i++)
        data[i] = nullptr;
}

size_t Spreadsheet::GetRows () const noexcept
{
    return rows;
}

size_t Spreadsheet::GetCols () const noexcept
{
    return cols;
}

Iterator Spreadsheet::Begin () const
{
    return Iterator(data);
}

Iterator Spreadsheet::End () const
{
    return data ? Iterator(data + (rows * cols) - 1) : Iterator(nullptr);
}

bool Spreadsheet::IsValidIterator (const Iterator &it) const
{
    return (!it.is_empty() && it >= Begin() && it <= End());
}

size_t Spreadsheet::GetAddress (const size_t row, const size_t col) const noexcept
{
    return (col - 1) + ( ( row - 1 ) * this->cols );
}

Iterator Spreadsheet::GetCell (const size_t row, const size_t col) const
{
    if (!data)
        throw std::logic_error("Spreadsheet.GetCell: Spreadsheet is currently empty.");

    if (row <= 0 || row > this->rows || col <= 0 || col > this->cols)
        throw std::out_of_range("Requested cell address is not in range of the spreadsheet.\n");

    Iterator result( data + GetAddress(row, col) );

    return result;
}

void Spreadsheet::SetCellValue (const size_t row, const size_t col, const char *value)
{
    if (!data)
        throw std::logic_error("Spreadsheet.SetCellValue: Spreadsheet is empty.");

    if (row <= 0 || row >= this->rows || col <= 0 || col >= this->cols)
        throw std::out_of_range("Given cell address is not in range of the spreadsheet.\n");

    size_t address = GetAddress(row, col);

    if (!data[address])
        data[address] = new std::string;

    *data[address] = value;
}

void Spreadsheet::SetCellValue (const size_t row, const size_t col, const std::string &value)
{
    SetCellValue(row, col, value.c_str());
}

void Spreadsheet::SetCellValue (const Iterator &it, const char *value)
{
    if (!IsValidIterator(it))
        throw std::out_of_range("Given cell address is not in range of the spreadsheet.\n");

    node* cell = data + (it - Begin());

    if (!*cell)
        *cell = new std::string;

    **cell = value;
}

void Spreadsheet::SetCellValue (const Iterator &it, const std::string &value)
{
    SetCellValue(it, value.c_str());
}

void Spreadsheet::Clear () noexcept
{
    if (!data)
        return;

    for (size_t i = 0; i < rows * cols; i++)
    {
        if (data[i])
            delete data[i];
    }

    delete[] data;
    data = nullptr;
}

void Spreadsheet::LoadFromFile (std::ifstream &file)
{
    size_t setRows(0), setCols(0), fullCells(0);
    csv::analyze_file(file, setRows, setCols, fullCells);

    if (!setRows || !setCols)
        throw std::logic_error("Given file has invalid spreadsheet dimensions.\n");

    node* buffer = new node[setRows * setCols];
    for (size_t i = 0; i < setRows * setCols; i++)
        buffer[i] = nullptr;

    file.clear();
    file.seekg(0, std::ios_base::beg);
    node *it = buffer;

    try
    {
        while (!file.eof())
        {
            char current;
            file.get(current);

            if (current == '\"')
            {
                *it = new std::string;
                csv::read_cell(**it, file);
            }

            if (current == ';')
                it++;
        }
    }
    catch (...)
    {
        for (size_t i = 0; i < it - buffer; i++)
        {
            if (buffer[i])
                delete buffer[i];
        }

        delete[] buffer;
        throw;
    }

    Clear();

    data = buffer;

    rows = setRows;
    cols = setCols;
}

void Spreadsheet::Serialize (std::ofstream &file) const
{
    if (!file)
        throw std::logic_error("Bad file stream.\n");

    Iterator it = GetCell(1, 1);

    while (it <= End())
    {
        if (it)
            file << '\"' << it.data() << '\"';

        size_t diff = it - Begin();
        if (diff && diff % cols == 0)
            file << '\n';

        file << ';';
        it++;
    }
}