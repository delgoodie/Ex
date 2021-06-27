#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_SizeOf (const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context) {
		double size = 0;
		if (rhs.type == Executor::Expr::Type::EX_NULL)
			size = 0;
		else if (rhs.type == Executor::Expr::Type::EX_BOOLEAN)
			size = 0;
		else if (rhs.type == Executor::Expr::Type::EX_STRING)
			size = rhs.string.length;
		else if (rhs.type == Executor::Expr::Type::EX_VARIABLE)
			size = 0;
		else if (rhs.type == Executor::Expr::Type::EX_OBJECT) {
			Executor::EvalLink* el = rhs.object.e_head;
			while (el && ++size) el = el->next;
		}

		return Executor::Result(Executor::Expr(size));
	}
}