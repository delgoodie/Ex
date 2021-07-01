#include "Operations.h"

#include <sstream>

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Add(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		CAST_VARS;

		// String Concat
		if (lhs->type == Executor::Expr::Type::EX_STRING || rhs->type == Executor::Expr::Type::EX_STRING)
		{
			CAST_PARAMS(Executor::Expr::Type::EX_STRING);

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