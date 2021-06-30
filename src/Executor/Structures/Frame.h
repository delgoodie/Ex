#pragma once

#include "Expr.h"
#include "Object.h"

namespace Executor {
	struct EvalLink;

	struct Frame {
		enum class ReturnSide : unsigned char {
			LHS,
			RHS
		};
		Expr dot;

		EvalLink* e_curr;
		int e_index;

		int lhs_size;
		int rhs_size;

		ReturnSide side;

		Expr parameter;
	};
}