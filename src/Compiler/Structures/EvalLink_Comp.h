#pragma once

#include "Expr_Comp.h"

namespace Compiler {
    struct EvalLink_Comp
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
        struct {
            int index;
            int jump;
        } op;
        Expr_Comp expr;
        EvalLink_Comp* next;

        EvalLink_Comp(Side s, Expr_Comp x) : type(Type::EXPR), side(s), expr(x), lhs(false), rhs(false), next(nullptr) {}
        EvalLink_Comp(Side s, bool l, bool r, int index) : type(Type::OP), side(s), lhs(l), rhs(r), op({ index, 0 }), next(nullptr) {}
        EvalLink_Comp(Side s, bool l, bool r, int index, int jump) : type(Type::OP), side(s), lhs(l), rhs(r), op({ index, jump }), next(nullptr) {}
		~EvalLink_Comp();

        unsigned char Flags();

        static Type TypeFromFlags(unsigned char flags);
        static Side SideFromFlags(unsigned char flags);
        static bool LhsFromFlags(unsigned char flags);
        static bool RhsFromFlags(unsigned char flags);
        static bool NullFromFlags(unsigned char flags);
    };
}