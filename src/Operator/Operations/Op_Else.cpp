#include "../Executor/ExecutorCore.h"

#include "Conversion.h"

namespace Operator {
	Executor::Result Op_Else (const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context) {
		if (Conversion::Convert(lhs, Executor::Expr::Type::EX_BOOLEAN, context).boolean)
			return Executor::Result(lhs, false, true);
		else
			return Executor::Result();
	}
}