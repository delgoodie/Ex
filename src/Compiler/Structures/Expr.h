#pragma once

#include <string>

#include "../../Core.h"


namespace Compiler {

	struct EvalLink;

    struct Expr
    {
        enum class Type : unsigned char
        {
            EX_BOOLEAN,
            EX_NUMBER,
            EX_STRING,
            EX_VARIABLE,
            EX_OBJECT,
            EX_NULL
        };
        Type type;
        ex_boolean_t boolean;
        ex_number_t number;
        std::string string;
		std::string variable;
        EvalLink* object;

        Expr() : type(Type::EX_NULL) {}
        Expr(ex_boolean_t b) : type(Type::EX_BOOLEAN), boolean(b) {}
        Expr(ex_number_t n) : type(Type::EX_NUMBER), number(n) {}
        Expr(std::string s) : type(Type::EX_STRING), string(s) {}
        Expr(std::string n, std::nullptr_t* v) : type(Type::EX_VARIABLE), variable(n) {}
        Expr(EvalLink* o) : type(Type::EX_OBJECT), object(o) {}
        Expr(std::nullptr_t null) : type(Type::EX_NULL) {}

        static std::string TypeToString(Expr::Type type);

        std::string ToString() const;
    };
}