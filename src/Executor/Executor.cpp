#include "Executor.h"

#include "ExecutorCore.h"

#include "Loader/Loader.h"
#include "Evaluator/Evaluator.h"
#include "Unloader/Unloader.h"

namespace Executor {
	Expr Execute(Blob blob) {
		Context *context = Load(blob);

		DEBUG_LOG(Debug::PrintContext(context));

		Expr expr = Evaluate(context);

		switch (expr.type) {
		case Expr::Type::EX_NULL:
			std::printf("Null\n");
			break;
		case Expr::Type::EX_BOOLEAN:
			std::printf("%s\n", expr.boolean ? "true" : "false");
			break;
		case Expr::Type::EX_NUMBER:
			std::printf("%g\n", expr.number);
			break;
		case Expr::Type::EX_STRING:
			std::printf("string\n");
			break;
		case Expr::Type::EX_VARIABLE:
			std::printf("variable\n");
			break;
		case Expr::Type::EX_OBJECT:
			std::printf("object\n");
			break;
		}

		Unload(context);

		return Expr();
	}
}