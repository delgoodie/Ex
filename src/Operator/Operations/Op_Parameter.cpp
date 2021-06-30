#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Parameter(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		return context->top_frame->parameter;
	}
}