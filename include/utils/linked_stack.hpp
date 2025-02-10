#pragma once

#ifndef __LINKED_STACK_HEADER_INCLUDED__
#define __LINKED_STACK_HEADER_INCLUDED__

#include <new>
#include <stdexcept>

template <typename T>
class linked_stack
{

struct node
{
    node () : data(), next(nullptr) {}
    node (const T &val) : data(val), next(nullptr) {}

    T data;
    node *next;
};

// Constructors
public:
    linked_stack () : tos(nullptr) {}

    linked_stack (const linked_stack/*<T>*/ &other) = delete;

    ~linked_stack ()
    { clear(); }

// Operators
public:
    linked_stack &operator= (const linked_stack/*<T>*/ &other) = delete;

// Methods
public:
    bool is_empty () const noexcept
    { return !tos; }

    bool is_full () const noexcept
    { return !spare && !(spare = new (std::nothrow) node); }

    T &top ()
    {
        if (!tos)
            throw std::logic_error("Called top() on empty stack.\n");

        return tos->data;
    }

    const T &top () const
    {
        if (is_empty())
            throw std::logic_error("Called top() on empty stack.\n");

        return tos->data;
    }

    void push (const T &value)
    {
        if (is_full())
            throw std::overflow_error("Stack is full.\n");

        node *buffer = new (std::nothrow) node(value);
        if (!buffer)
        {
            buffer = spare;
            spare = nullptr;
        }

        buffer->next = tos;
        tos = buffer;
    }

    T pop ()
    {
        if (is_empty())
            throw std::underflow_error("Stack is empty.\n");

        T result(top());

        node *toDelete = tos;
        tos = tos->next;

        delete toDelete;
        return result;
    }

    void clear () noexcept
    {
        while (tos)
        {
            node *toDelete = tos;
            tos = tos->next;

            delete toDelete;
        }
    }

// Members
private:
    node *tos;
    mutable node *spare = nullptr;

};

#endif // __LINKED_STACK_HEADER_INCLUDED__