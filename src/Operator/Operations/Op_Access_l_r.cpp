#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Access_l_r (const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context) {
		return Executor::Result(Executor::Expr(nullptr));
	}
}