#pragma once

#include <string>

#include "Expr.h"

namespace Compiler {
    struct Node
    {
        enum class Type
        {
            OP,
            EXPR
        };
        Type type;
        Expr expr;
        struct {
            int index;
            int jump;
        } op;

        Node* lhs;
        Node* rhs;
        bool expanded;
        bool flattened;

		Node(Expr x) : type(Type::EXPR), expr(x), op({-1, 0}), lhs(nullptr), rhs(nullptr), expanded(false), flattened(false) {}
        Node(int i) : type(Type::OP), op({ i, 0 }), expr(Expr(nullptr)), lhs(nullptr), rhs(nullptr), expanded(false), flattened(false) {}
        std::string ToString() const;
    };
}