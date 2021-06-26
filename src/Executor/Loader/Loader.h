#pragma once

#include "../ExecutorCore.h"

namespace Executor {
	Context* Load(Blob blob);

	namespace Debug {
		void PrintContext(Context* context);
	}
}