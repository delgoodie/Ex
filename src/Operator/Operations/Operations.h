#pragma once
#pragma once

#include "../Executor/ExecutorCore.h"

#include "Conversion.h"

#define CAST_PARAMS(TYPE) *lhs = Conversion::Convert(*lhs, TYPE, context);\
*rhs = Conversion::Convert(*rhs, TYPE, context);

#define CAST_VARS if (lhs->type == Executor::Expr::Type::EX_VARIABLE) *lhs = Conversion::ConvertVariable(*lhs, context);\
if (rhs->type == Executor::Expr::Type::EX_VARIABLE) *rhs = Conversion::ConvertVariable(*rhs, context);

namespace Operator
{
	Executor::Result Op_Access_Binary(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Access_Unary_L(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Access_Unary_R(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Access_Nullary(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Assign(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);

	Executor::Result Op_If(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Else(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Return(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Comma_Binary(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Comma_Unary(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Jump(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Catch(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);

	Executor::Result Op_Parameter(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Eval_r(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Eval_l_r(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);

	Executor::Result Op_False(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_SizeOf(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Add(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);

	Executor::Result Op_Exponent(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Modulus(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Multiply(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Divide(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Subtract_Unary(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Subtract_Binary(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);

	Executor::Result Op_LessThan(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_GreaterThan(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_LessThanOrEqualTo(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_GreaterThanOrEqualTo(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Not(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_And(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_Or(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_EqualTo(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);
	Executor::Result Op_NotEqualTo(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);

	Executor::Result(*const FUNC[NUM_OPS])(Executor::Expr*, Executor::Expr*, Executor::Context*) = {
		Op_Parameter,				// $
		Op_False,                   // !   
		Op_Access_Binary,           // .
		Op_Access_Unary_L,          // .
		Op_Access_Unary_R,          // .
		Op_Access_Nullary,          // .
		Op_Eval_l_r,                // ^
		Op_Eval_r,                  // ^
		Op_SizeOf,                  // #
		Op_Subtract_Unary,          // -
		Op_Not,                     // !
		Op_Exponent,                // **
		Op_Modulus,                 // %
		Op_Multiply,                // *
		Op_Divide,                  // /
		Op_Add,						// +
		Op_Subtract_Binary,         // -
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
		Op_Assign,                  // =
		Op_Return,                  // ->
		Op_Comma_Binary,            // ,
		Op_Comma_Unary,             // ,
		Op_Jump,					// ;
		Op_Catch					// :
	};
}
