#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Access_l_r(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		return Executor::Result(Executor::Expr(nullptr));
	}
}