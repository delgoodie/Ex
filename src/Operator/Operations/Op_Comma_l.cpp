#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Comma_l (const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context) {
		return Executor::Result(lhs);
	}
}