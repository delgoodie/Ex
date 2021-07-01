#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Jump(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		Executor::EvalLink* el = context->top_frame->e_curr;
		int i = 0;
		while (!el->TypeFlag() || el->op.index != CATCH_INDEX) {
			el = el->prev;
			i--;
		}

		context->top_frame->e_curr->op.jump = i;

		return Executor::Result(false, true);
	}
}