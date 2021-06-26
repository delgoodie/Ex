#pragma once

#include <string>

#include "Expr_Comp.h"

namespace Compiler {
    struct Node_Comp
    {
        enum class Type
        {
            OP,
            EXPR
        };
        Type type;
        Expr_Comp expr;
        struct {
            int index;
            int jump;
        } op;

        Node_Comp* lhs;
        Node_Comp* rhs;
        bool expanded;
        bool flattened;

		Node_Comp(Expr_Comp x) : type(Type::EXPR), expr(x), op({-1, 0}), lhs(nullptr), rhs(nullptr), expanded(false), flattened(false) {}
        Node_Comp(int i) : type(Type::OP), op({ i, 0 }), expr(Expr_Comp(nullptr)), lhs(nullptr), rhs(nullptr), expanded(false), flattened(false) {}
        std::string ToString() const;
    };
}