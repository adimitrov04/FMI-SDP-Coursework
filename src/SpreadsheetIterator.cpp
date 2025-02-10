#include "../include/Spreadsheet.h"

#include <stdexcept>

using Iterator = Spreadsheet::Iterator;

// ------- OPERATORS -------

Iterator::operator bool () const noexcept
{
    return *current;
}

size_t Iterator::operator- (const Iterator &other) const noexcept
{
    return current - other.current;
}

bool Iterator::operator== (const Iterator &other) const noexcept
{
    return current == other.current;
}

bool Iterator::operator< (const Iterator &other) const noexcept
{
    return current < other.current;
}

bool Iterator::operator> (const Iterator &other) const noexcept
{
    return current > other.current;
}

bool Iterator::operator<= (const Iterator &other) const noexcept
{
    return current <= other.current;
}

bool Iterator::operator>= (const Iterator &other) const noexcept
{
    return current >= other.current;
}

Iterator &Iterator::operator= (const Iterator &other) noexcept
{
    if (this != &other)
    {
        current = other.current;
    }

    return *this;
}

std::string Iterator::operator* ()
{
    return data();
}

const std::string Iterator::operator* () const
{
    return data();
}

Iterator &Iterator::operator++ ()
{
    current = this->next().current;

    return *this;
}

Iterator Iterator::operator++ (int)
{
    current = this->next().current;

    return *this;
}

Iterator &Iterator::operator-- ()
{
    current = this->prev().current;

    return *this;
}

Iterator Iterator::operator-- (int)
{
    current = this->prev().current;

    return *this;
}

// -------- METHODS --------

bool Iterator::is_empty() const noexcept
{
    return !current;
}

Iterator Iterator::next () const
{
    return Iterator(current + 1);
}

Iterator Iterator::prev () const
{
    return Iterator(current - 1);
}

std::string Iterator::data ()
{
    if (!current)
        throw std::runtime_error("Iterator.data: iterator is nullptr.\n");

    if (*current)
        return **current;

    return std::string("0");
}

const std::string Iterator::data () const
{
    if (current)
        return **current;

    return std::string("0");
}