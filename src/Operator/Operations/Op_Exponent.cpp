#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Exponent(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		CAST_PARAMS(Executor::Expr::Type::EX_NUMBER);
		return Executor::Result(Executor::Expr(pow(lhs->number, rhs->number)));
	}
}