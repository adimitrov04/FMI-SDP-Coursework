#pragma once

#ifndef __CSVFILEFUNCTIONS_HEADER_INCLUDED__
#define __CSVFILEFUNCTIONS_HEADER_INCLUDED__

#include <fstream>
#include <cstddef>
#include <string>

namespace csv
{

void skip_cell (std::ifstream &file) noexcept;

void analyze_file (std::ifstream &file, size_t &outRows, size_t &outCols, size_t &outFullCount);

void read_cell (std::string &dest, std::ifstream &file);

}

#endif //__CSVFILEFUNCTIONS_HEADER_INCLUDED__
