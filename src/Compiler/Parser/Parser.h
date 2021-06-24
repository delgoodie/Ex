#pragma once

#include <vector>

#include "../CompilerCore.h"

namespace Compiler
{
	std::vector<Node> Parse(const std::vector<Token>& tokens);
    namespace Debug
    {
		void PrintNodeFlat(const std::vector<Node>& node_flat);
    }
}