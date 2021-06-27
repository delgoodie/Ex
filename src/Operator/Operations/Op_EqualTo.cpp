#include "../Executor/ExecutorCore.h"

#include "Conversion.h"

namespace Operator {
	Executor::Result Op_EqualTo (const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context) {
        ex_boolean_t value = false;
        if (lhs.type == Executor::Expr::Type::EX_STRING || rhs.type == Executor::Expr::Type::EX_STRING) // String Comparison
        {
            Executor::Expr c_lhs = Conversion::Convert(lhs, Executor::Expr::Type::EX_STRING);
            Executor::Expr c_rhs = Conversion::Convert(rhs, Executor::Expr::Type::EX_STRING);

            std::string lhs_str = c_lhs.string.head->ToString(), rhs_str = c_rhs.string.head->ToString();
            value = lhs_str.compare(rhs_str) == 0;
        }
        else if (lhs.type == Executor::Expr::Type::EX_NUMBER || rhs.type == Executor::Expr::Type::EX_NUMBER) // Number comparison
        {
            Executor::Expr c_lhs = Conversion::Convert(lhs, Executor::Expr::Type::EX_NUMBER);
            Executor::Expr c_rhs = Conversion::Convert(rhs, Executor::Expr::Type::EX_NUMBER);
            value = c_lhs.number == c_rhs.number; // TODO: rounding support? 0 == 1e-9
        }
        else if (lhs.type == Executor::Expr::Type::EX_BOOLEAN || rhs.type == Executor::Expr::Type::EX_BOOLEAN) // Boolean Comparison
        {
            Executor::Expr c_lhs = Conversion::Convert(lhs, Executor::Expr::Type::EX_BOOLEAN);
            Executor::Expr c_rhs = Conversion::Convert(rhs, Executor::Expr::Type::EX_BOOLEAN);
            value = c_lhs.boolean == c_rhs.boolean;
        }
        else if (lhs.type == Executor::Expr::Type::EX_OBJECT && rhs.type == Executor::Expr::Type::EX_OBJECT) // Object Comparison
        {
            //TODO: Object comparison
            value = false;
        }
        else
        {
            //TODO: handle other cases
            value = false;
        }
        return Executor::Result(Executor::Expr(value));
	}
}