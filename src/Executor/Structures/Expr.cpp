#include "Expr.h"

#include "StringLink.h"
#include "EvalLink.h"

namespace Executor {
    std::string Expr::ToString() const {
        switch (type) {
        case Type::EX_NULL:
            return "null";
        case Type::EX_BOOLEAN:
            return boolean ? "true" : "false";
        case Type::EX_NUMBER:
            return std::to_string(number);
        case Type::EX_STRING:
            return "'" + string.head->ToString() + "'";
        case Type::EX_VARIABLE:
            return "`" + variable.name_head->ToString() + "`";
        case Type::EX_OBJECT:
            return "{ " + object.e_head->ToString() + "}";
        }
        return "no type";
    }
}