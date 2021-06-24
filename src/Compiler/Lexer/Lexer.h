#pragma once

#include <string>
#include <vector>

#include "../CompilerCore.h"

namespace Compiler
{
	std::vector<Token> Lex(const char* code);

	namespace Debug {
		void PrintTokens(const std::vector<Token>& tokens);
	}
}