#pragma once

namespace Executor {
	struct EvalLink;
	struct VarLink;

	struct Object {
		EvalLink* e_head;
		VarLink* v_head;
	};
}