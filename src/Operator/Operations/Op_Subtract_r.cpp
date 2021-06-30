#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Subtract_r(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		if (rhs->type == Executor::Expr::Type::EX_NUMBER) return Executor::Result(Executor::Expr(-rhs->number));
		else return Executor::Result(nullptr);
	}
}