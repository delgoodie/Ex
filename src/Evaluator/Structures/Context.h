#pragma once

#include "../Core.h"

#include "Stack.h"
#include "Heap.h"

namespace Evaluator {
    struct Expr;
    struct EvalLink;
    struct VarLink;
    struct ListLink;
    struct StringLink;

    struct Context
    {
        Stack<Expr, EX_EXPR_STACK_SIZE> ExprStack;
        Heap<EvalLink, EX_EVAL_HEAP_SIZE> EvalHeap;
        Heap<VarLink, EX_VAR_HEAP_SIZE> VarHeap;
        Heap<ListLink, EX_LIST_HEAP_SIZE> ListHeap;
        Heap<StringLink, EX_STRING_HEAP_SIZE> StringHeap;
        Stack<Object, EX_OBJECT_STACK_SIZE> ObjectStack;
        EvalLink* entry;
    };
}