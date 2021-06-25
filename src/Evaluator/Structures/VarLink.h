#pragma once

#include "Expr.h"

namespace Evaluator {
    struct StringLink;

    struct VarLink
    {
        VarLink* prev;
        StringLink* name;
        Expr expr;
        VarLink* next;
    };
}