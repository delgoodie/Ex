#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Or(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		CAST_PARAMS(Executor::Expr::Type::EX_BOOLEAN);
		return Executor::Result(Executor::Expr(lhs->boolean || rhs->boolean));
	}
}