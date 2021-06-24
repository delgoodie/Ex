#pragma once

#include <string>

#include "../CompilerCore.h"

namespace Compiler {
    struct Expr
    {
        enum class Type
        {
            EX_BOOLEAN,
            EX_NUMBER,
            EX_STRING,
            EX_VARIABLE,
            EX_OBJECT,
            EX_NULL
        };
        Type type;
        union
        {
            ex_boolean_t boolean;
            ex_number_t number;
            std::string string;
            std::string variable;
            Object object;
        };

        Expr() : type(Type::EX_NULL) {}
        Expr(ex_boolean_t b) : type(Type::EX_BOOLEAN), boolean(b) {}
        Expr(ex_number_t n) : type(Type::EX_NUMBER), number(n) {}
        Expr(std::string s) : type(Type::EX_STRING), string(s) {}
        Expr(std::string n, std::nullptr_t* v) : type(Type::EX_VARIABLE), variable(n) {}
        Expr(Object o) : type(Type::EX_OBJECT), object(o) {}
        Expr(std::nullptr_t null) : type(Type::EX_NULL) {}

        Expr(const Expr& expr);
        Expr& operator=(const Expr& expr);
        ~Expr();

        static std::string TypeToString(Expr::Type type);

        std::string ToString();
    };
}