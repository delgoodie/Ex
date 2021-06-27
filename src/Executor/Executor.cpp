#include "Executor.h"

#include <sstream>

#include "ExecutorCore.h"

#include "Loader/Loader.h"
#include "Evaluator/Evaluator.h"
#include "Unloader/Unloader.h"

namespace Executor {
	Expr Execute(Blob blob) {
		Context *context = Load(blob);

		DEBUG_LOG(Debug::PrintContext(context));

		Expr expr = Evaluate(context);

		std::printf("Result: %s\n", expr.ToString().c_str());

		Unload(context);

		return Expr();
	}
}