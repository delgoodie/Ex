#pragma once

#include <vector>

#include "../CompilerCore.h"

namespace Compiler
{
	std::vector<Node_Comp> Parse(const std::vector<Token_Comp>& tokens);
    namespace Debug
    {
		void PrintNodeFlat(const std::vector<Node_Comp>& node_flat);
    }
}