#pragma once
#include <string>

namespace Compiler {
    struct Token
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
		Token(Type t, std::string v, int l) : type(t), value(v), line(l) {}
    };
}