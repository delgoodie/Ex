#include "Operations.h"

#include "../Executor/ExecutorCore.h"

namespace Operator {
	Executor::Result Op_Access_Binary(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context) {
		Executor::Object left;
		switch (lhs->type) {
		case Executor::Expr::Type::EX_NULL:
			throw "Can't access property of null!";
			break;
		case Executor::Expr::Type::EX_BOOLEAN:
			*lhs = Conversion::Convert(*lhs, Executor::Expr::Type::EX_NUMBER, context);
		case Executor::Expr::Type::EX_NUMBER:
			left = context->PeekFrame(static_cast<int>(lhs->number))->dot.variable.link->expr.object;
			break;
		case Executor::Expr::Type::EX_VARIABLE:
			left = Conversion::ConvertVariable(*lhs, context).object;
			break;
		case Executor::Expr::Type::EX_STRING:
			left = Conversion::FindVariable(*lhs, context->top_frame->dot.variable.link, context)->expr.object;
			break;
		case Executor::Expr::Type::EX_OBJECT:
			left = lhs->object;
		}

		switch (rhs->type) {
		case Executor::Expr::Type::EX_NULL:
			throw "Can't access 'null' property of object!";
			break;
		case Executor::Expr::Type::EX_BOOLEAN:
			*rhs = Conversion::Convert(*rhs, Executor::Expr::Type::EX_NUMBER, context);
		case Executor::Expr::Type::EX_NUMBER:
			throw "Indexing objects not yet implemented!";
			break;
		case Executor::Expr::Type::EX_VARIABLE:
		case Executor::Expr::Type::EX_STRING:
			return Executor::Expr(nullptr, Conversion::FindVariable(*rhs, left.v_head, context));
			break;
		case Executor::Expr::Type::EX_OBJECT:
			throw "Can't access {} property of object!";
		}

		return Executor::Result(Executor::Expr(nullptr));
	}
}