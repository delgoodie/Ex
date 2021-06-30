#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Eval_r(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		Executor::Frame frame;

		Executor::VarLink* vl = context->VarHeap.Allocate();
		vl->prev = nullptr;
		vl->next = nullptr;
		vl->name = nullptr;
		vl->expr = *rhs;

		frame.dot = Executor::Expr(nullptr, vl);
		frame.e_curr = frame.dot.variable.ptr->expr.object.e_head;
		frame.lhs_size = 0;
		frame.rhs_size = 0;
		frame.side = context->top_frame->e_curr->SideFlag() ? Executor::Frame::ReturnSide::LHS : Executor::Frame::ReturnSide::LHS;

		context->PushFrame(frame);
		return Executor::Result(false, false);
	}
}