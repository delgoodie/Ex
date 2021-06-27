#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Access (const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context) {
		return Executor::Result(Executor::Expr(context->top_frame->object));
	}
}