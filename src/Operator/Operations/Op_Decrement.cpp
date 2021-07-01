#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Decrement(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		if (lhs->type == Executor::Expr::Type::EX_VARIABLE) {
			Executor::VarLink* vl = lhs->variable.link;
			if (!vl) vl = Conversion::FindVariable(*lhs, context->top_frame->dot.variable.link->expr.object.v_head, context);
			if (!vl) throw "variable does not exist";

			if (vl->expr.type == Executor::Expr::Type::EX_NUMBER) {
				vl->expr.number--;
			}
			else throw "cant decrement non-number";

			return Executor::Result(Executor::Expr(vl->name, vl));
		}
		else throw "cant decrement non-variable";
	}
}