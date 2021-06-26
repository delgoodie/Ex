#pragma once

#include <string.h>
#include <stdlib.h>

namespace Executor {
    /*
        Heap preallocated, fixed size, strongly typed heap
        Heap is divided into many slots, each the size of the Heap type
        The heap can allocate and free data optimally
    */
    template <typename T, size_t L>
    class Heap
    {
    private:
        // Pointer to beginning of Heap
        T* begin;
        // bit packed map of heap - 0 = free slot, 1 = used slot
        unsigned char map[L / 8];
        // cached index of the first free element in the heap
        int first;


    public:
        Heap()
        {
            begin = (T*)malloc(Size());
            memset(begin, 0x00, Size());
            memset(map, 0b00000000, L / 8);
        }
        constexpr size_t Stride() { return sizeof(T); }

        constexpr size_t Size() { return Stride() * L; }

        T* Allocate(T element)
        {
            T* element_ptr = new (&begin[first]) T(element);
            SetFree(first, false);

            while (!IsFree(first))
                first++;
            return element_ptr;
        } //TODO: test alloc and map bit operations

        void Free(T* element)
        {
            int index = (element - begin) / Stride();
            SetFree(index, true);
            if (index < first)
                first = index;
        }

        // Move these functions to private and create Iterator to traverse used data

        T* Begin() { return begin; }

        // Checks if slot in heap is free - false = used, true = free
        bool IsFree(int index)
        {
            return ~map[index / 8] & (0b00000001 << (index % 8));
        }

        // Sets the status of a slot in the heap at index - false = used, true = free
        void SetFree(int index, bool free)
        {
            if (free)
                map[index / 8] &= ~(0b00000001 << (index % 8));
            else
                map[index / 8] |= (0b00000001 << (index % 8));
        }
    };
}