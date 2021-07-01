#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Access_Unary_L(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		*lhs = Conversion::Convert(*lhs, Executor::Expr::Type::EX_NUMBER, context);
		return Executor::Result(context->PeekFrame(static_cast<int>(lhs->number))->dot.variable.link->expr);
	}
}