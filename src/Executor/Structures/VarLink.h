#pragma once

#include "Expr.h"

namespace Executor {
    struct StringLink;

    struct VarLink
    {
        VarLink* prev;
        StringLink* name;
        Expr expr;
        VarLink* next;
    };
}