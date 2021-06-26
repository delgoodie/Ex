#pragma once

#include "../ExecutorCore.h"

namespace Executor {
    namespace Operator
    {
        struct Result {
            Expr expr;
            unsigned char flags;
            unsigned int error_code;

            Result(Expr e) : expr(e), flags(0x80), error_code(0) {}
            Result(Expr e, bool return_f, bool exit_f, bool jump_f) : expr(e), flags((return_f << 7) | (exit_f << 6) | (jump_f << 5)), error_code(0) {}
            Result(Expr e, unsigned int ec) : expr(e), flags(0x10), error_code(ec) {}

            bool ReturnFlag() { return flags & 0x80; }
            bool ExitFlag() { return flags & 0x40; }
            bool JumpFlag() { return flags & 0x20; }
            bool ErrorFlag() { return flags & 0x10; }
        };

        namespace Conversion
        {
            Expr NumberToString(const Expr& expr);
            Expr StringToNumber(const Expr& expr);
            Expr NumberToBool(const Expr& expr);
            Expr BoolToNumber(const Expr& expr);
            Expr StringToBool(const Expr& expr);
            Expr BooleanToString(const Expr& expr);
            Expr ObjectToBoolean(const Expr& expr);
            Expr ObjectToString(const Expr& expr);
            Expr Convert(const Expr& expr, Expr::Type type);
        }

        namespace Object
        {
            Result Access_l_r(const Expr& lhs, const Expr& rhs, Context* context);
            Result Access_r(const Expr& lhs, const Expr& rhs, Context* context);
            Result Access(const Expr& lhs, const Expr& rhs, Context* context);
            Result Assign(const Expr& lhs, const Expr& rhs, Context* context);
        }

        namespace Control
        {
            Result If(const Expr& lhs, const Expr& rhs, Context* context);
            Result While(const Expr& lhs, const Expr& rhs, Context* context);
            Result Else(const Expr& lhs, const Expr& rhs, Context* context);
            Result Return(const Expr& lhs, const Expr& rhs, Context* context);
            Result Comma_l_r(const Expr& lhs, const Expr& rhs, Context* context);
            Result Comma_l(const Expr& lhs, const Expr& rhs, Context* context);
        }

        namespace Literal
        {
            Result False(const Expr& lhs, const Expr& rhs, Context* context);
            Result Eval_r(const Expr& lhs, const Expr& rhs, Context* context);
            Result Eval_l_r(const Expr& lhs, const Expr& rhs, Context* context);
            Result SizeOf(const Expr& lhs, const Expr& rhs, Context* context);
            Result Exponent(const Expr& lhs, const Expr& rhs, Context* context);
            Result Modulus(const Expr& lhs, const Expr& rhs, Context* context);
            Result Multiply(const Expr& lhs, const Expr& rhs, Context* context);
            Result Divide(const Expr& lhs, const Expr& rhs, Context* context);
            Result Add_r(const Expr& lhs, const Expr& rhs, Context* context);
            Result Subtract_r(const Expr& lhs, const Expr& rhs, Context* context);
            Result Add_l_r(const Expr& lhs, const Expr& rhs, Context* context);
            Result Subtract_l_r(const Expr& lhs, const Expr& rhs, Context* context);
        }

        namespace Logic
        {
            Result LessThan(const Expr& lhs, const Expr& rhs, Context* context);
            Result GreaterThan(const Expr& lhs, const Expr& rhs, Context* context);
            Result LessThanOrEqualTo(const Expr& lhs, const Expr& rhs, Context* context);
            Result GreaterThanOrEqualTo(const Expr& lhs, const Expr& rhs, Context* context);
            Result Not(const Expr& lhs, const Expr& rhs, Context* context);
            Result And(const Expr& lhs, const Expr& rhs, Context* context);
            Result Or(const Expr& lhs, const Expr& rhs, Context* context);
            Result EqualTo(const Expr& lhs, const Expr& rhs, Context* context);
            Result NotEqualTo(const Expr& lhs, const Expr& rhs, Context* context);
        }

        Result(* const FUNC[NUM_OPS])(const Expr&, const Expr&, Context*) = {
            Literal::False,              // !
            Object::Access_l_r,          // .
            Object::Access_r,            // .
            Object::Access,              // .
            Literal::Eval_l_r,           // ^
            Literal::Eval_r,             // ^
            Literal::SizeOf,             // #
            Literal::Add_r,              // +
            Literal::Subtract_r,         // -
            Logic::Not,                  // !
            Literal::Exponent,           // **
            Literal::Modulus,            // %
            Literal::Multiply,           // *
            Literal::Divide,             // /
            Literal::Add_l_r,            // +
            Literal::Subtract_l_r,       // -
            Logic::LessThan,             // <
            Logic::GreaterThan,          // >
            Logic::LessThanOrEqualTo,    // <=
            Logic::GreaterThanOrEqualTo, // >=
            Logic::EqualTo,              // ==
            Logic::NotEqualTo,           // !=
            Logic::And,                  // &&
            Logic::Or,                   // ||
            Control::If,                 // ?
            Control::Else,               // |
            Control::While,              // ;
            Object::Assign,              // =
            Control::Return,             // ->
            Control::Comma_l_r,          // ,
            Control::Comma_l             // ,
        };
    }
}