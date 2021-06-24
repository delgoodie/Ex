#pragma once

#include <vector>

#include "../CompilerCore.h"

namespace Compiler
{
	Node* Expand(std::vector<Node>& node_flat);

	namespace Debug {
		void PrintNodeTree(Node* root);
	}
}