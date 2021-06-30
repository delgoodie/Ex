#pragma once

#include "Expr.h"

namespace Executor {
	struct Result {
		Expr expr;
		unsigned char flags;
		unsigned int error_code;

		const unsigned char RETURN_FLAG = 0x80;
		const unsigned char EXIT_FLAG = 0x40;
		const unsigned char NO_ERROR_FLAG = 0x20; // Must be on for no error, that way, 0x00 is an error
		const unsigned char JUMP_FLAG = 0x10;
		const unsigned char FRAME_SWITCH_FLAG = 0x08;

		Result() : expr(Expr(nullptr)), flags(0x00), error_code(0) {
			flags |= NO_ERROR_FLAG;
		}
		Result(bool exit_f) : expr(Expr(nullptr)), flags(0x00), error_code(0) {
			flags |= exit_f * EXIT_FLAG;
			flags |= NO_ERROR_FLAG;
		}
		Result(bool exit_f, bool jump_f) : expr(Expr(nullptr)), flags(0x00), error_code(0) {
			flags |= exit_f * EXIT_FLAG;
			flags |= jump_f * JUMP_FLAG;
			flags |= NO_ERROR_FLAG;
		}
		Result(bool exit_f, bool jump_f, bool frame_switch_f) : expr(Expr(nullptr)), flags(0x00), error_code(0) {
			flags |= exit_f * EXIT_FLAG;
			flags |= jump_f * JUMP_FLAG;
			flags |= frame_switch_f * FRAME_SWITCH_FLAG;
			flags |= NO_ERROR_FLAG;
		}
		Result(Expr e) : expr(e), flags(0x00), error_code(0) {
			flags |= RETURN_FLAG;
			flags |= NO_ERROR_FLAG;
		}
		Result(Expr e, bool exit_f) : expr(e), flags(0x00), error_code(0) {
			flags |= RETURN_FLAG;
			flags |= exit_f * EXIT_FLAG;
			flags |= NO_ERROR_FLAG;
		}
		Result(Expr e, bool exit_f, bool jump_f) : expr(e), flags(0x00), error_code(0) {
			flags |= RETURN_FLAG;
			flags |= exit_f * EXIT_FLAG;
			flags |= jump_f * JUMP_FLAG;
			flags |= NO_ERROR_FLAG;
		}
		Result(Expr e, bool exit_f, bool jump_f, bool frame_switch_f) : expr(e), flags(0x00), error_code(0) {
			flags |= RETURN_FLAG;
			flags |= exit_f * EXIT_FLAG;
			flags |= jump_f * JUMP_FLAG;
			flags |= jump_f * FRAME_SWITCH_FLAG;
			flags |= NO_ERROR_FLAG;
		}
		Result(unsigned int ec) : expr(Expr(nullptr)), flags(0x00), error_code(ec) {}

		bool ReturnFlag() { return flags & RETURN_FLAG; }
		bool ExitFlag() { return flags & EXIT_FLAG; }
		bool ErrorFlag() { return !(flags & NO_ERROR_FLAG); }
		bool JumpFlag() { return flags & JUMP_FLAG; }
		bool FrameSwitchFlag() { return flags & FRAME_SWITCH_FLAG; }
	};
}