#pragma once

#include "Expr.h"

namespace Evaluator {

    struct EvalLink
    {
        EvalLink* prev;
        /*
            Flags:
            2^7 - EvalLink Type Flag (0 = expr, 1 = op)
            2^6 - EvalLink Side Flag (0 = rhs, 1 = lhs)
            2^5 - Consumes LHS Flag (0 = false, 1 = true)
            2^4 - Consumes RHS Flag (0 = false, 1 = true)
            2^3 - Null EvalLink Flag (only used for chain termination)
            2^2 - Unused bit
            2^1 - Unused bit
            2^0 - Unused bit
        */
        unsigned char flags;
        union
        {
            struct {
                int index;
                int jump;
            } op;
            Expr expr;
        };
        EvalLink* next;
        EvalLink() = default;
        EvalLink(unsigned char f) : flags(f) {}

        // 0 = expr, 1 = op
        bool TypeFlag();
        // 0 = rhs, 1 = lhs
        bool SideFlag();
        //  0 = false, 1 = true
        bool LHSFlag();
        //  0 = false, 1 = true
        bool RHSFlag();
        // 0 = non-null, 1 = null (used for chain termination)
        bool NullFlag();
    };
}