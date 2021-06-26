#pragma once


namespace Executor {
	struct EvalLink;
	struct VarLink;
	
	struct Frame {
		enum class ReturnSide : unsigned char {
			LHS,
			RHS
		};
		EvalLink* e_head;
		VarLink* v_head;
		
		EvalLink* e_curr;
		int e_index;

		int lhs_size;
		int rhs_size;

		ReturnSide side;
	};
}