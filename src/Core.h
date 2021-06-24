#pragma once

#define NUM_OPS 31

typedef double ex_number_t;
typedef bool ex_boolean_t;

struct Blob
{
    unsigned char* data;
    size_t size;
};