#include "Expr.h"

#include <sstream>

namespace Compiler {
    Expr::Expr(const Expr& expr)
    {
        type = expr.type;
        switch (type) {
        case Type::EX_BOOLEAN:
            boolean = expr.boolean;
            break;
        case Type::EX_NUMBER:
            number = expr.number;
            break;
        case Type::EX_STRING:
            string = expr.string;
            break;
        case Type::EX_VARIABLE:
            variable = expr.variable;
            break;
        case Type::EX_OBJECT:
            object = expr.object;
            break;
        case Type::EX_NULL:
            boolean = false;
            break;
        }
    }
    
    Expr& Expr::operator=(const Expr& expr) {
        type = expr.type;
        switch (type) {
        case Type::EX_BOOLEAN:
            boolean = expr.boolean;
            break;
        case Type::EX_NUMBER:
            number = expr.number;
            break;
        case Type::EX_STRING:
            string = expr.string;
            break;
        case Type::EX_VARIABLE:
            variable = expr.variable;
            break;
        case Type::EX_OBJECT:
            object = expr.object;
            break;
        case Type::EX_NULL:
            boolean = false;
            break;
        }
    }

    Expr::~Expr() {
        if (type == Type::EX_STRING) string.~basic_string();
        else if (type == Type::EX_VARIABLE) variable.~basic_string();
    }

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

    std::string Expr::ToString()
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