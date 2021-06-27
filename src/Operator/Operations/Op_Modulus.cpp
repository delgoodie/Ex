#include "../Executor/ExecutorCore.h"

#include "Conversion.h"

namespace Operator {
	Executor::Result Op_Modulus (const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context) {
		Executor::Expr c_lhs = Conversion::Convert(lhs, Executor::Expr::Type::EX_NUMBER);
		Executor::Expr c_rhs = Conversion::Convert(rhs, Executor::Expr::Type::EX_NUMBER);
		return Executor::Result(Executor::Expr((ex_number_t)((int)c_lhs.number % (int)c_rhs.number)));
	}
}