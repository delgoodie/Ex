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
		enum class Side {
			LHS,
			RHS,
			NONE
		};
		Side side;
        Expr_Comp expr;
        struct {
            int index;
            int jump;
        } op;

        Node_Comp* lhs;
        Node_Comp* rhs;
        bool expanded;
		bool part_flattened;
        bool flattened;

		Node_Comp(Expr_Comp x) : type(Type::EXPR), side(Side::NONE), expr(x), op({-1, 0}), lhs(nullptr), rhs(nullptr), expanded(false), part_flattened(false), flattened(false) {}
        Node_Comp(int i) : type(Type::OP), side(Side::NONE), op({ i, 0 }), expr(Expr_Comp(nullptr)), lhs(nullptr), rhs(nullptr), expanded(false), part_flattened(false), flattened(false) {}
        std::string ToString() const;
    };
}