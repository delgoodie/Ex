#pragma once

#include "Expr.h"

namespace Executor {
    struct Result {
        Expr expr;
        unsigned char flags;
        unsigned int error_code;

        Result(Expr e) : expr(e), flags(0x80), error_code(0) {}
        Result(bool exit_f, bool jump_f) : expr(Expr(nullptr)), flags((exit_f << 6) | (jump_f << 5)), error_code(0) {}
        Result(Expr e, bool return_f, bool exit_f, bool jump_f) : expr(e), flags((return_f << 7) | (exit_f << 6) | (jump_f << 5)), error_code(0) {}
        Result(Expr e, unsigned int ec) : expr(e), flags(0x10), error_code(ec) {}

        bool ReturnFlag() { return flags & 0x80; }
        bool ExitFlag() { return flags & 0x40; }
        bool JumpFlag() { return flags & 0x20; }
        bool ErrorFlag() { return flags & 0x10; }
    };
}