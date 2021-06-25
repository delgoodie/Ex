#pragma once

#include "Expr.h"

namespace Evaluator {
    struct ListLink
    {
        ListLink* prev;
        Expr expr;
        ListLink* next;
    };
}