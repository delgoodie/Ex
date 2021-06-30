#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_If(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		if (Conversion::Convert(*lhs, Executor::Expr::Type::EX_BOOLEAN, context).boolean) {
			return Executor::Result();
		}
		else
			return Executor::Result(Executor::Expr(false), false, true);
	}
}