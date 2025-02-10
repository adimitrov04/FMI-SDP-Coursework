#pragma once

#ifndef __SPREADSHEET_HEADER_INCLUDED__
#define __SPREADSHEET_HEADER_INCLUDED__

#include <fstream>
#include <cstddef>
#include <string>

class Spreadsheet
{

using node = std::string*;

public:

class Iterator
{

public:
    explicit Iterator (node *initial) : current(initial) {}
    Iterator (const Iterator &other) : current(other.current) {}

    ~Iterator () = default;

public:
    operator bool() const noexcept;

    bool operator== (const Iterator &other) const noexcept;
    bool operator< (const Iterator &other) const noexcept;
    bool operator> (const Iterator &other) const noexcept;
    bool operator<= (const Iterator &other) const noexcept;
    bool operator>= (const Iterator &other) const noexcept;

    Iterator &operator= (const Iterator &other) noexcept;

    std::string operator* ();
    const std::string operator* () const;

    size_t operator- (const Iterator &other) const noexcept;

    Iterator operator++ (int);
    Iterator &operator++ ();
    Iterator operator-- (int);
    Iterator &operator-- ();

public:
    bool is_empty () const noexcept;

    Iterator next () const;
    Iterator prev () const;

    std::string data ();
    const std::string data () const;

private:
    Iterator () : current(nullptr) {}

private:
    node* current;

};

// Constructors
public:
    Spreadsheet () : data{ nullptr, }, rows(0), cols(0) {}
    Spreadsheet (int setRows, int setCols);
    Spreadsheet (std::ifstream &file);
    Spreadsheet (const Spreadsheet &other) = delete;

    ~Spreadsheet ();

// Operators
public:
    Spreadsheet &operator= (const Spreadsheet &other) = delete;

// Methods
public:
    void CreateNew (size_t setRows, size_t setCols);

    size_t GetRows () const noexcept;
    size_t GetCols () const noexcept;

    Iterator Begin () const;
    Iterator End () const;
    bool IsValidIterator (const Iterator &it) const;

    Iterator GetCell (const size_t row, const size_t col) const;

    void SetCellValue (const size_t row, const size_t col, const char* value);
    void SetCellValue (const size_t row, const size_t col, const std::string &value);
    void SetCellValue (const Iterator &it, const char* value);
    void SetCellValue (const Iterator &it, const std::string& value);

    void Clear () noexcept;
    void LoadFromFile (std::ifstream &file);
    void Serialize (std::ofstream &file) const;

private:
    // May give invalid address, checks are necessary
    size_t GetAddress (const size_t row, const size_t col) const noexcept;

// Members
private:
    node* data;
    size_t rows, cols;

};

#endif //__SPREADSHEET_HEADER_INCLUDED__
