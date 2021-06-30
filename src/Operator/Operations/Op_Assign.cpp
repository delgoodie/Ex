#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Assign(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		if (lhs->type == Executor::Expr::Type::EX_VARIABLE) {
			Executor::VarLink* vl = Conversion::FindVariable(*lhs, context);
			vl->expr = rhs;
			return Executor::Result(Executor::Expr(lhs->variable.name_head, vl));
		}
		else std::printf("Error trying to assign non-variable\n");
	}
}