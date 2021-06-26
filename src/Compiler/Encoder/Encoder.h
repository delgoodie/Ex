#pragma once

#include "../CompilerCore.h"

namespace Compiler
{
	Blob Encode(EvalLink_Comp* head);

	namespace Debug {
		void PrintRawBlob(Blob blob);
	}
}
