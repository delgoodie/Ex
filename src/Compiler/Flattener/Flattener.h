#pragma once

#include "../CompilerCore.h"

namespace Compiler
{
	EvalLink* Flatten(Node* root);

	namespace Debug {
		void PrintLinkChain(EvalLink* head);
	}
}