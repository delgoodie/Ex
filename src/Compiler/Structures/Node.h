#pragma once

#include <string>

#include "../CompilerCore.h"

namespace Compiler {
    struct Node
    {
        enum class Type
        {
            OP,
            EXPR
        };
        Type type;
        union
        {
            Expr expr;
            struct {
                int index;
                int jump;
            } op;
        };

        Node* lhs;
        Node* rhs;
        bool expanded;
        bool flattened;

        Node(Expr x) : type(Type::EXPR), expr(x), lhs(nullptr), rhs(nullptr), expanded(false), flattened(false) {}
        Node(int i) : type(Type::OP), op({ i, 0 }), lhs(nullptr), rhs(nullptr), expanded(false), flattened(false) {}
        Node(const Node& node);
        std::string ToString();
    };
}