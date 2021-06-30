#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Modulus(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		CAST_PARAMS(Executor::Expr::Type::EX_NUMBER);
		return Executor::Result(Executor::Expr((ex_number_t)(static_cast<int>(lhs->number) % static_cast<int>(rhs->number))));
	}
}