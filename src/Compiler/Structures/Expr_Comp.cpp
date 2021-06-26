#include "Expr_Comp.h"

#include <sstream>

#include "EvalLink_Comp.h"

namespace Compiler {
    std::string Expr_Comp::TypeToString(Expr_Comp::Type type)
    {
        switch (type)
        {
        case Expr_Comp::Type::EX_BOOLEAN:
            return "BOOLEAN";
        case Expr_Comp::Type::EX_NUMBER:
            return "NUMBER";
        case Expr_Comp::Type::EX_STRING:
            return "STRING";
        case Expr_Comp::Type::EX_OBJECT:
            return "OBJECT";
        case Expr_Comp::Type::EX_NULL:
            return "NULL";
        default:
            return "Invalid Type";
        }
    }

    std::string Expr_Comp::ToString() const
    {
        std::stringstream ss;
        switch (type)
        {
        case Expr_Comp::Type::EX_VARIABLE:
            ss << variable;
            break;
        case Expr_Comp::Type::EX_BOOLEAN:
            ss << (boolean ? "true" : "false");
            break;
        case Expr_Comp::Type::EX_NUMBER:
            ss << number;
            break;
        case Expr_Comp::Type::EX_STRING:
            ss << string;
            break;
        case Expr_Comp::Type::EX_OBJECT:
            ss << "{}";
            break;
        default:
            ss << "Invalid";
        }
        return ss.str();
    }
}