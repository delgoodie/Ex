#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Not(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		*rhs = Conversion::Convert(*rhs, Executor::Expr::Type::EX_BOOLEAN, context);
		return Executor::Result(Executor::Expr(!rhs->boolean));
	}
}