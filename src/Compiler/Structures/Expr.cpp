#include "Expr.h"

#include <sstream>

#include "EvalLink.h"

namespace Compiler {
    std::string Expr::TypeToString(Expr::Type type)
    {
        switch (type)
        {
        case Expr::Type::EX_BOOLEAN:
            return "BOOLEAN";
        case Expr::Type::EX_NUMBER:
            return "NUMBER";
        case Expr::Type::EX_STRING:
            return "STRING";
        case Expr::Type::EX_OBJECT:
            return "OBJECT";
        case Expr::Type::EX_NULL:
            return "NULL";
        default:
            return "Invalid Type";
        }
    }

    std::string Expr::ToString() const
    {
        std::stringstream ss;
        switch (type)
        {
        case Expr::Type::EX_VARIABLE:
            ss << variable;
            break;
        case Expr::Type::EX_BOOLEAN:
            ss << (boolean ? "true" : "false");
            break;
        case Expr::Type::EX_NUMBER:
            ss << number;
            break;
        case Expr::Type::EX_STRING:
            ss << string;
            break;
        case Expr::Type::EX_OBJECT:
            ss << "{}";
            break;
        default:
            ss << "Invalid";
        }
        return ss.str();
    }
}