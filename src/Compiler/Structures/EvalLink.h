#pragma once

#include "Expr.h"

namespace Compiler {
    struct EvalLink
    {
        enum class Type : unsigned char
        {
            OP,
            EXPR
        };
        enum class Side : unsigned char
        {
            LHS,
            RHS
        };

        Type type;
        Side side;
        bool lhs;
        bool rhs;
        unsigned short op_index;
        Expr expr;
        EvalLink* next;

        EvalLink(Side s, Expr x) : type(Type::EXPR), side(s), expr(x), lhs(false), rhs(false), next(nullptr) {}
        EvalLink(Side s, bool l, bool r, int oi) : type(Type::OP), side(s), lhs(l), rhs(r), op_index(oi), next(nullptr) {}
		~EvalLink();

        unsigned char Flags();

        static Type TypeFromFlags(unsigned char flags);
        static Side SideFromFlags(unsigned char flags);
        static bool LhsFromFlags(unsigned char flags);
        static bool RhsFromFlags(unsigned char flags);
        static bool NullFromFlags(unsigned char flags);
    };
}