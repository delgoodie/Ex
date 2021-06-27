#include "../Executor/ExecutorCore.h"

#include "Conversion.h"

namespace Operator {
	Executor::Result Op_Subtract_l_r (const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context) {
		//TODO: remove property from object
		Executor::Expr c_lhs = Conversion::Convert(lhs, Executor::Expr::Type::EX_NUMBER);
		Executor::Expr c_rhs = Conversion::Convert(rhs, Executor::Expr::Type::EX_NUMBER);
		return Executor::Result(Executor::Expr(c_lhs.number - c_rhs.number));
	}
}