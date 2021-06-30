#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Catch(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		return Executor::Result(Executor::Expr(nullptr));
	}
}