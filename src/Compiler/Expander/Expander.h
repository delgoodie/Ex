#pragma once

#include <vector>

#include "../CompilerCore.h"

namespace Compiler
{
	Node_Comp* Expand(std::vector<Node_Comp>& node_flat);

	namespace Debug {
		void PrintNodeTree(Node_Comp* root);
	}
}