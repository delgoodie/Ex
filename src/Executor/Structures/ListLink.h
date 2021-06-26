#pragma once

#include "Expr.h"

namespace Executor {
    struct ListLink
    {
        ListLink* prev;
        Expr expr;
        ListLink* next;
    };
}