#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Assign(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		Executor::VarLink* vl;
		if (lhs->type == Executor::Expr::Type::EX_VARIABLE && lhs->variable.link) vl = lhs->variable.link;
		else {
			Executor::VarLink*& v_head = context->top_frame->dot.variable.link->expr.object.v_head;
			vl = Conversion::FindVariable(*lhs, v_head, context);

			// Adding new variable
			if (!vl) {
				vl = context->VarHeap.Allocate();
				vl->expr = Executor::Expr(nullptr);
				vl->prev = nullptr;

				if (lhs->type == Executor::Expr::Type::EX_VARIABLE) vl->name = lhs->variable.name_head;
				else if (lhs->type == Executor::Expr::Type::EX_STRING) vl->name = lhs->string.head;
				else throw "Error trying to add variable to object that isn't var or string";

				// Push new variable to top of Variable Chain for faster access
				vl->next = v_head;
				if (v_head) v_head->prev = vl;
				v_head = vl;
			}
		}

		if (rhs->type == Executor::Expr::Type::EX_VARIABLE) *rhs = Conversion::ConvertVariable(*rhs, context);

		vl->expr = *rhs;
		return Executor::Result(Executor::Expr(vl->name, vl));
	}
}