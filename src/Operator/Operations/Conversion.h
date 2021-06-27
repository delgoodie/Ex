#pragma once

#include "../Executor/ExecutorCore.h"

namespace Operator {
    namespace Conversion
    {
        Executor::Expr NumberToString(const Executor::Expr& expr);
        Executor::Expr StringToNumber(const Executor::Expr& expr);
        Executor::Expr NumberToBool(const Executor::Expr& expr);
        Executor::Expr BoolToNumber(const Executor::Expr& expr);
        Executor::Expr StringToBool(const Executor::Expr& expr);
        Executor::Expr BooleanToString(const Executor::Expr& expr);
        Executor::Expr ObjectToBoolean(const Executor::Expr& expr);
        Executor::Expr ObjectToString(const Executor::Expr& expr);
        Executor::Expr Convert(const Executor::Expr& expr, Executor::Expr::Type type);
    }
}