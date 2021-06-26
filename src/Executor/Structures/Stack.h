#pragma once

#include <stdlib.h>

namespace Executor {
    /*
    Heap preallocated, fixed size, strongly typed stack
    The stack has two parts:
    Bottom: elements appended to the beginning of the stack
    Top: elements prepended to the end of the stack
    Think if the memory was turned on its side so 0x00 was at the bottom and 0xFF was at the top

    Stack also checks for overflow (bottom > top)
    */
    template <typename T, size_t L>
    class Stack
    {
    private:
        // Pointer to beginning of stack memory block
        T* begin;
        // index of last element at top of stack
        int top;
        // index of first element of bottom of stack
        int bottom;

        // true = overflow, false = safe
        bool OverflowCheck()
        {
            return bottom + 1 > top;
        }

    public:
        Stack()
        {
            begin = (T*)malloc(Size());
            bottom = 0;
            top = L - 1;
        }

        constexpr size_t Size() { return L * sizeof(T); }

        constexpr size_t Stride() { return sizeof(T); }

        void TopPush(T element)
        {
            top--;
            if (!OverflowCheck())
                new (&begin[top]) T(element); //TODO: is this fastest? is element being moved? or memcpy() or const& or T* element
        }

        void BottomPush(T element) //TODO: test alloc and top, bottom manip
        {
            bottom++;
            if (!OverflowCheck())
                new (&begin[bottom]) T(element);
        }

        T TopPop()
        {
            return T(begin[top++]);
        }

        T BottomPop()
        {
            T element(begin[bottom]);
            bottom--;
            return element;
        }

        T* PeekBottom(int index) {
            if (index < bottom) return &begin[bottom - index];
            else return nullptr;
        }

        T* PeekTop(int index) {
            if (index < L - top) return &begin[top + index];
            else return nullptr;
        }
    };
}