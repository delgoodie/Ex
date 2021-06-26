#pragma once

#define NUM_OPS 31

#define EX_EXPR_STACK_SIZE 1000
#define EX_EVAL_HEAP_SIZE 1000
#define EX_VAR_HEAP_SIZE 1000
#define EX_LIST_HEAP_SIZE 1000
#define EX_STRING_HEAP_SIZE 1000
#define EX_FRAME_STACK_SIZE 1000

#ifdef _DEBUG
#define DEBUG_LOG(x) x
#else
#define DEBUG_LOG(x)
#endif

#include "Blob.h"

typedef double ex_number_t;
typedef bool ex_boolean_t;