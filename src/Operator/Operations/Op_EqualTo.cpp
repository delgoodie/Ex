#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_EqualTo(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		ex_boolean_t value = false;
		if (lhs->type == Executor::Expr::Type::EX_STRING || rhs->type == Executor::Expr::Type::EX_STRING) // String Comparison
		{
			CAST_PARAMS(Executor::Expr::Type::EX_STRING);

			std::string lhs_str = lhs->string.head->ToString(), rhs_str = rhs->string.head->ToString();
			value = lhs_str.compare(rhs_str) == 0;
		}
		else if (lhs->type == Executor::Expr::Type::EX_NUMBER || rhs->type == Executor::Expr::Type::EX_NUMBER) // Number comparison
		{
			CAST_PARAMS(Executor::Expr::Type::EX_NUMBER);
			value = lhs->number == rhs->number; // TODO: rounding support? 0 == 1e-9
		}
		else if (lhs->type == Executor::Expr::Type::EX_BOOLEAN || rhs->type == Executor::Expr::Type::EX_BOOLEAN) // Boolean Comparison
		{
			CAST_PARAMS(Executor::Expr::Type::EX_BOOLEAN);

			value = lhs->boolean == rhs->boolean;
		}
		else if (lhs->type == Executor::Expr::Type::EX_OBJECT && rhs->type == Executor::Expr::Type::EX_OBJECT) // Object Comparison
		{
			//TODO: Object comparison
			value = false;
		}
		else
		{
			//TODO: handle other cases
			value = false;
		}
		return Executor::Result(Executor::Expr(value));
	}
}