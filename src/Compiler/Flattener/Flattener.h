#pragma once

#include "../CompilerCore.h"

namespace Compiler
{
	EvalLink_Comp* Flatten(Node_Comp* root);

	namespace Debug {
		void PrintLinkChain(EvalLink_Comp* head);
	}
}