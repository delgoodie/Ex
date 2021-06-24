#pragma once

#include <string>
#include <vector>

#include "../CompilerCore.h"

namespace Compiler
{
	std::vector<Token> Lex(const std::string& code);
}
