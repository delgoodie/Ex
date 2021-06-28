#pragma once

#include "../Executor/ExecutorCore.h"

#include "Conversion.h"

namespace Operator
{
    Executor::Result Op_Access_l_r(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Access_r(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Access(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Assign(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);

    Executor::Result Op_If(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_While(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Else(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Return(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Comma_l_r(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Comma_l(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);

    Executor::Result Op_False(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Eval_r(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Eval_l_r(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_SizeOf(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Exponent(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Modulus(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Multiply(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Divide(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Add_r(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Subtract_r(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Add_l_r(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Subtract_l_r(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);

    Executor::Result Op_LessThan(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_GreaterThan(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_LessThanOrEqualTo(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_GreaterThanOrEqualTo(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Not(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_And(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_Or(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_EqualTo(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);
    Executor::Result Op_NotEqualTo(const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context);

    Executor::Result(* const FUNC[NUM_OPS])(const Executor::Expr&, const Executor::Expr&,  Executor::Context*) = {
        Op_False,                   // !
        Op_Access_l_r,              // .
        Op_Access_r,                // .
        Op_Access,                  // .
        Op_Eval_l_r,                // ^
        Op_Eval_r,                  // ^
        Op_SizeOf,                  // #
        Op_Add_r,                   // +
        Op_Subtract_r,              // -
        Op_Not,                     // !
        Op_Exponent,                // **
        Op_Modulus,                 // %
        Op_Multiply,                // *
        Op_Divide,                  // /
        Op_Add_l_r,                 // +
        Op_Subtract_l_r,            // -
        Op_LessThan,                // <
        Op_GreaterThan,             // >
        Op_LessThanOrEqualTo,       // <=
        Op_GreaterThanOrEqualTo,    // >=
        Op_EqualTo,                 // ==
        Op_NotEqualTo,              // !=
        Op_And,                     // &&
        Op_Or,                      // ||
        Op_If,                      // ?
        Op_Else,                    // |
        Op_While,                   // ;
        Op_Assign,                  // =
        Op_Return,                  // ->
        Op_Comma_l_r,               // ,
        Op_Comma_l                  // ,
    };
}
