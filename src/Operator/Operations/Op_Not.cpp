#include "../Executor/ExecutorCore.h"

#include "Conversion.h"

namespace Operator {
	Executor::Result Op_Not (const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context) {
		Executor::Expr c_rhs = Conversion::Convert(rhs, Executor::Expr::Type::EX_BOOLEAN, context);
		return Executor::Result(Executor::Expr(!c_rhs.boolean));
	}
}