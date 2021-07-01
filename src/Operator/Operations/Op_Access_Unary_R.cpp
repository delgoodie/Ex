#include "Operations.h"

#include "../Executor/ExecutorCore.h"

#include <string>

namespace Operator {

	Executor::Result Op_Access_Unary_R(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {

		Executor::VarLink*& v_head = context->top_frame->dot.variable.link->expr.object.v_head, *vl = Conversion::FindVariable(*rhs, v_head, context);
		if (!vl) {  // Adding new variable
			vl = context->VarHeap.Allocate();
			vl->expr = Executor::Expr(nullptr);
			vl->prev = nullptr;

			if (rhs->type == Executor::Expr::Type::EX_VARIABLE) vl->name = rhs->variable.name_head;
			else if (rhs->type == Executor::Expr::Type::EX_STRING) vl->name = rhs->string.head;
			else throw "Error trying to add variable to object that isn't var or string";

			// Push new variable to top of Variable Chain for faster access
			vl->next = v_head;
			if (v_head) v_head->prev = vl;
			v_head = vl;
		}
		return Executor::Result(Executor::Expr(vl->name, vl));
	}
}