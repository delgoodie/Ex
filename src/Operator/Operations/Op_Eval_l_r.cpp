#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Eval_l_r (const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context) {
		Executor::Frame frame;
		frame.object = rhs.object;
		frame.e_curr = rhs.object.e_head;
		frame.lhs_size = 0;
		frame.rhs_size = 0;
		frame.parameter = lhs;
		frame.side = context->top_frame->e_curr->SideFlag() ? Executor::Frame::ReturnSide::LHS : Executor::Frame::ReturnSide::LHS;

		context->PushFrame(frame);
		return Executor::Result(false, false);
	}
}