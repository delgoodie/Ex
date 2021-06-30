#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Else(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		if (Conversion::Convert(*lhs, Executor::Expr::Type::EX_BOOLEAN, context).boolean)
			return Executor::Result(*lhs, false, true);
		else
			return Executor::Result();
	}
}