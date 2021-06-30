#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Eval_r(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		Executor::Frame frame;

		Executor::VarLink* dot = context->VarHeap.Allocate();
		if (rhs->type == Executor::Expr::Type::EX_OBJECT) {
			dot->prev = nullptr;
			dot->next = nullptr;
			dot->name = nullptr;
			dot->expr = *rhs;
		}
		else {
			if (rhs->variable.link) dot = rhs->variable.link;
			else dot = Conversion::FindVariable(*rhs, context->top_frame->dot.variable.link->expr.object.v_head, context);
		}

		frame.dot = Executor::Expr(nullptr, dot);
		frame.e_curr = frame.dot.variable.link->expr.object.e_head;
		frame.lhs_size = 0;
		frame.rhs_size = 0;
		frame.side = context->top_frame->e_curr->SideFlag() ? Executor::Frame::ReturnSide::LHS : Executor::Frame::ReturnSide::RHS;

		context->top_frame->e_curr = context->top_frame->e_curr->next;

		context->PushFrame(frame);
		return Executor::Result(false, false, true);
	}
}