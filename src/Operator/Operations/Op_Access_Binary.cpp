#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Access_Binary(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		Executor::Object* left = nullptr;

		// LHS => Object
		switch (lhs->type) {
		case Executor::Expr::Type::EX_NULL:
			throw "Can't access property of null!";
			break;
		case Executor::Expr::Type::EX_BOOLEAN:
			*lhs = Conversion::Convert(*lhs, Executor::Expr::Type::EX_NUMBER, context);
		case Executor::Expr::Type::EX_NUMBER:
			left = &context->PeekFrame(static_cast<int>(lhs->number))->dot.variable.link->expr.object;
			break;
		case Executor::Expr::Type::EX_VARIABLE:
			if (lhs->variable.link) lhs = &lhs->variable.link->expr;
			else lhs = &Conversion::FindVariable(*lhs, context->top_frame->dot.variable.link->expr.object.v_head, context)->expr;
			if (lhs->type == Executor::Expr::Type::EX_OBJECT) {
				left = &lhs->object;
			}
			else {
				throw "Can't access property of non-object";
			}
			break;
		case Executor::Expr::Type::EX_STRING:
			lhs = &Conversion::FindVariable(*lhs, context->top_frame->dot.variable.link->expr.object.v_head, context)->expr;
			if (lhs->type == Executor::Expr::Type::EX_OBJECT) {
				left = &lhs->object;
			}
			else {
				throw "Can't access property of non-object";
			}
			break;
		case Executor::Expr::Type::EX_OBJECT:
			left = &lhs->object;
		}

		if (!left) throw "Invalid LHS of . accessor";

		// RHS => Property of Object
		if (rhs->type == Executor::Expr::Type::EX_NUMBER)
			throw "Indexing objects not yet implemented!";
		else if (rhs->type == Executor::Expr::Type::EX_VARIABLE || rhs->type == Executor::Expr::Type::EX_STRING) {
			Executor::VarLink* vl = Conversion::FindVariable(*rhs, left->v_head, context);
			if (!vl) {  // Adding new variable
				vl = context->VarHeap.Allocate();
				vl->expr = Executor::Expr(nullptr);
				vl->prev = nullptr;

				if (rhs->type == Executor::Expr::Type::EX_VARIABLE) vl->name = rhs->variable.name_head;
				else if (rhs->type == Executor::Expr::Type::EX_STRING) vl->name = rhs->string.head;
				else throw "Error trying to add variable to object that isn't var or string";

				// Push new variable to top of Variable Chain for faster access
				vl->next = left->v_head;
				if (left->v_head) left->v_head->prev = vl;
				left->v_head = vl;
			}
			return Executor::Result(Executor::Expr(vl->name, vl));
		}
		else
			throw "Can't access {}/bool/null property of object!";
	}
}