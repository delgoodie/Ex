#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_While (const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context) {
		return Executor::Result(Executor::Expr(nullptr));
	}
}