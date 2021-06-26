#pragma once

#include <string>

#include "../../Core.h"


namespace Compiler {

	struct EvalLink_Comp;

    struct Expr_Comp
    {
        enum class Type : unsigned char
        {
            EX_NULL = 0,
            EX_BOOLEAN = 1,
            EX_NUMBER = 2,
            EX_STRING = 3,
            EX_VARIABLE = 4,
            EX_OBJECT = 5
        };
        Type type;
        ex_boolean_t boolean;
        ex_number_t number;
        std::string string;
		std::string variable;
        EvalLink_Comp* object;

        Expr_Comp() : type(Type::EX_NULL) {}
        Expr_Comp(ex_boolean_t b) : type(Type::EX_BOOLEAN), boolean(b) {}
        Expr_Comp(ex_number_t n) : type(Type::EX_NUMBER), number(n) {}
        Expr_Comp(std::string s) : type(Type::EX_STRING), string(s) {}
        Expr_Comp(std::string n, std::nullptr_t* v) : type(Type::EX_VARIABLE), variable(n) {}
        Expr_Comp(EvalLink_Comp* o) : type(Type::EX_OBJECT), object(o) {}
        Expr_Comp(std::nullptr_t null) : type(Type::EX_NULL) {}

        static std::string TypeToString(Expr_Comp::Type type);

        std::string ToString() const;
    };
}