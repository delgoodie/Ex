#pragma once

#include "../CompilerCore.h"

namespace Compiler
{
	Blob Encode(EvalLink* head);

	namespace Debug {
		void PrintRawBlob(Blob blob);
	}
}
