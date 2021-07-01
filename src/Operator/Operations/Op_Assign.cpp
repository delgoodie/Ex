#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Assign(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		if (lhs->type == Executor::Expr::Type::EX_VARIABLE) {
			Executor::VarLink* vl;
			if (lhs->variable.link) vl = lhs->variable.link;
			else vl = Conversion::FindVariable(*lhs, context->top_frame->dot.variable.link->expr.object.v_head, context);

			if (rhs->type == Executor::Expr::Type::EX_VARIABLE) *rhs = Conversion::ConvertVariable(*rhs, context);

			vl->expr = *rhs;
			return Executor::Result(Executor::Expr(lhs->variable.name_head, vl));
		}
		else std::printf("Error trying to assign non-variable\n");
	}
}