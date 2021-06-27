#include "../Executor/ExecutorCore.h"

#include "Conversion.h"

namespace Operator {
	Executor::Result Op_Else (const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context) {
		if (!Conversion::Convert(lhs, Executor::Expr::Type::EX_BOOLEAN).boolean)
			return Executor::Result(lhs, true, false, true);
		else
			return Executor::Result(false, true);
	}
}