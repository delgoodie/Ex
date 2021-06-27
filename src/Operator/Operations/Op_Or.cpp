#include "../Executor/ExecutorCore.h"

#include "Conversion.h"

namespace Operator {
	Executor::Result Op_Or (const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context) {
		Executor::Expr c_lhs = Conversion::Convert(lhs, Executor::Expr::Type::EX_BOOLEAN);
		Executor::Expr c_rhs = Conversion::Convert(rhs, Executor::Expr::Type::EX_BOOLEAN);
		return Executor::Result(Executor::Expr(c_lhs.boolean || c_rhs.boolean));
	}
}