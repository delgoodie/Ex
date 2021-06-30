#pragma once

#include "../Executor/ExecutorCore.h"

namespace Operator {
	namespace Conversion
	{
		size_t StringLength(Executor::StringLink* sl);
		Executor::StringLink* StdStringToString(std::string string, Executor::Context* context);
		Executor::Expr NumberToString(Executor::Expr expr, Executor::Context* context);
		Executor::Expr StringToNumber(Executor::Expr expr);
		Executor::Expr NumberToBool(Executor::Expr expr);
		Executor::Expr BoolToNumber(Executor::Expr expr);
		Executor::Expr StringToBool(Executor::Expr expr);
		Executor::Expr BooleanToString(Executor::Expr expr, Executor::Context* context);
		Executor::Expr ObjectToBoolean(Executor::Expr expr);
		Executor::Expr ObjectToString(Executor::Expr expr, Executor::Context* context);
		Executor::VarLink* FindVariable(Executor::Expr expr, Executor::Context* context);
		Executor::Expr ConvertVariable(Executor::Expr expr, Executor::Context* context);
		Executor::Expr Convert(Executor::Expr expr, Executor::Expr::Type type, Executor::Context* context);
	}
}