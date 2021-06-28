#pragma once

#include "Expr.h"

namespace Executor {
    struct Result {
        Expr expr;
        unsigned char flags;
        unsigned int error_code;

        const unsigned char RETURN_FLAG = 0x80;
        const unsigned char EXIT_FLAG = 0x40;
        const unsigned char NO_ERROR_FLAG = 0x20; // Must be on for no error

        Result() : expr(Expr(nullptr)), flags(NO_ERROR_FLAG), error_code(0) {}
        Result(bool exit_f) : expr(Expr(nullptr)), flags(exit_f * EXIT_FLAG | NO_ERROR_FLAG), error_code(0) {}
        Result(Expr e) : expr(e), flags(RETURN_FLAG | NO_ERROR_FLAG), error_code(0) {}
        Result(Expr e, bool exit_f) : expr(e), flags((RETURN_FLAG) | exit_f * EXIT_FLAG | NO_ERROR_FLAG), error_code(0) {}
        Result(unsigned int ec) : expr(Expr(nullptr)), flags(0x00), error_code(ec) {}

        bool ReturnFlag() { return flags & RETURN_FLAG; }
        bool ExitFlag() { return flags & EXIT_FLAG; }
        bool ErrorFlag() { return !(flags & NO_ERROR_FLAG); }
    };
}