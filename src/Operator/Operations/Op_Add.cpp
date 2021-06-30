#include "Operations.h"

#include <sstream>

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Add(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {

		// Add property
		if (lhs->type == Executor::Expr::Type::EX_OBJECT || lhs->type == Executor::Expr::Type::EX_VARIABLE && Conversion::FindVariable(*lhs, context)->expr.type == Executor::Expr::Type::EX_OBJECT) {

			Executor::VarLink* vl = context->VarHeap.Allocate();
			vl->expr = Executor::Expr(nullptr);
			vl->prev = nullptr;
			if (rhs->type == Executor::Expr::Type::EX_VARIABLE) vl->name = rhs->variable.name_head;
			else if (rhs->type == Executor::Expr::Type::EX_STRING) vl->name = rhs->string.head;
			else {
				std::printf("Error trying to add variable to object that isn't var or string\n");
			}

			if (lhs->type == Executor::Expr::Type::EX_OBJECT) {
				vl->next = lhs->object.v_head;
				if (lhs->object.v_head) lhs->object.v_head->prev = vl;
				lhs->object.v_head = vl;
			}
			else {
				Executor::VarLink* varobj = Conversion::FindVariable(*lhs, context);
				vl->next = varobj->expr.object.v_head;
				if (varobj->expr.object.v_head) varobj->expr.object.v_head->prev = vl;
				varobj->expr.object.v_head = vl;
			}


			return Executor::Result(Executor::Expr(vl->name, vl));
		}

		CAST_VARS;

		// String Concat
		if (lhs->type == Executor::Expr::Type::EX_STRING || rhs->type == Executor::Expr::Type::EX_STRING)
		{
			*lhs = Conversion::Convert(lhs, Executor::Expr::Type::EX_STRING, context);
			*rhs = Conversion::Convert(rhs, Executor::Expr::Type::EX_STRING, context);

			std::string sum = lhs->string.head->ToString() + rhs->string.head->ToString();

			Executor::StringLink* head = nullptr, *curr = context->StringHeap.Allocate(), *prev = nullptr;
			int length = sum.length();

			for (int i = 0; i < length; i++) {
				if (i % 5 == 0 && i > 0) {
					if (!prev) head = curr;
					else prev->next = curr;
					curr->prev = prev;
					prev = curr;
					curr = context->StringHeap.Allocate();
				}
				curr->string[i % 5] = sum[i];
			}

			if (prev) prev->next = curr;
			if (!head) head = curr;
			if (length % 5) curr->string[length % 5] = '\0';
			curr->next = nullptr;

			return Executor::Result(Executor::Expr(head, length));
		}
		// Numeric Addition
		else if (lhs->type == Executor::Expr::Type::EX_NUMBER || rhs->type == Executor::Expr::Type::EX_NUMBER) // Numerical Addition
		{
			CAST_PARAMS(Executor::Expr::Type::EX_NUMBER);
			return Executor::Result(Executor::Expr(lhs->number + rhs->number));
		}
		// Bool OR
		else if (lhs->type == Executor::Expr::Type::EX_BOOLEAN && rhs->type == Executor::Expr::Type::EX_BOOLEAN)
		{
			return Executor::Result(Executor::Expr(lhs->boolean || rhs->boolean));
		}
		else
		{
			// unsupported value
			return Executor::Result(Executor::Expr(nullptr));
		}
	}
}