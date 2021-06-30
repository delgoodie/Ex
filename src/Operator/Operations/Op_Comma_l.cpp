#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Comma_l(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		return Executor::Result(*lhs);
	}
}