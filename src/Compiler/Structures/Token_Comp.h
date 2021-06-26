#pragma once
#include <string>

namespace Compiler {
    struct Token_Comp
    {
        enum class Type
        {
            NUM,
            STR,
            VAR,
            OP,
            PRE
        };

        Type type;
        std::string value;
        int line;
		Token_Comp(Type t, std::string v, int l) : type(t), value(v), line(l) {}
    };
}