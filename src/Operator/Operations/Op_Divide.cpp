#include "../Executor/ExecutorCore.h"

#include "Conversion.h"

namespace Operator {
	Executor::Result Op_Divide (const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context) {
		Executor::Expr c_lhs = Conversion::Convert(lhs, Executor::Expr::Type::EX_NUMBER);
		Executor::Expr c_rhs = Conversion::Convert(rhs, Executor::Expr::Type::EX_NUMBER);
		// TODO: divide by zero error
		return Executor::Result(Executor::Expr(c_lhs.number / c_rhs.number));
	}
}