#include "Expander.h"

#include "Expander.h"

#include <iostream>
#include <vector>
#include <iostream>

#include "../CompilerCore.h"


static int Pow2(int exp)
{
	int num = 1;
	for (int i = 0; i < exp; i++)
		num *= 2;
	return num;
}

static void PrintSpaces(int num_spaces)
{
	for (int i = 0; i < num_spaces; i++)
		std::printf(" ");
}


namespace Compiler {
    Node* Expand(std::vector<Node>& node_flat)
    {
        if (node_flat.size() == 0)
            std::printf("0 nodes\n");
		// Iterate over non-ops and set expanded to true
		for (int i = 0; i < node_flat.size(); i++) if (node_flat[i].type == Node::Type::EXPR) node_flat[i].expanded = true;

        // Iterate over ops and expand by prec
        while (node_flat.size() > 1)
        {
            int mindex = -1;

            // find highest prec unexpanded op
			for (int i = 0; i < node_flat.size(); i++)
			{
				bool isOp = node_flat[i].type == Node::Type::OP;
				bool isntExpanded = !node_flat[i].expanded;
				bool lhsGood = !Operator::LHS[node_flat[i].op.index] || i > 0 && node_flat[i - 1].expanded;
				bool rhsGood = !Operator::RHS[node_flat[i].op.index] || i + 1 < node_flat.size() && node_flat[i + 1].expanded;
				bool mindexGood = mindex == -1 || Operator::PREC[node_flat[i].op.index] < Operator::PREC[node_flat[mindex].op.index];

				if (isOp && isntExpanded && lhsGood && rhsGood && mindexGood)
						mindex = i;
			}
			/*
                if (node_flat[i].type == Node::Type::OP &&
                    !node_flat[i].expanded &&
                    (!Operator::LHS[node_flat[i].op.index] || i > 0 && node_flat[i - 1].expanded) &&
                    (!Operator::RHS[node_flat[i].op.index] || i + 1 < node_flat.size() && node_flat[i + 1].expanded) &&
                    (mindex == -1 || Operator::PREC[node_flat[i].op.index] < Operator::PREC[node_flat[mindex].op.index]))
                    mindex = i;
			*/

            if (mindex == -1)
            {
                // TODO: throw
                std::printf("2+ unmergable nodes\n");
            }
            else
            {
                // RHS first because index shifts when LHS removed
                if (Operator::RHS[node_flat[mindex].op.index])
                {
                    Node* rhs = new Node(node_flat[mindex + 1]);
                    node_flat.erase(node_flat.begin() + mindex + 1);
                    node_flat[mindex].rhs = rhs;
                }
                if (Operator::LHS[node_flat[mindex].op.index])
                {
                    Node* lhs = new Node(node_flat[mindex - 1]);
                    node_flat.erase(node_flat.begin() + mindex - 1);
                    mindex--;
                    node_flat[mindex].lhs = lhs;
                }
                node_flat[mindex].expanded = true;
            }
        }

        return new Node(node_flat[0]);
    }

	namespace Debug {
		void PrintNodeTree(Node* root)
		{
			std::printf("Printing Node Tree:\n\n");
			int depth = 0;
			int num_spaces = 64;
			int it = 1;
			bool no_children = false;

			while (!no_children)
			{
				PrintSpaces(num_spaces / 2);
				no_children = true;
				for (int i = 1; i <= it; i++)
				{
					Node* n = root;
					for (int d = 1; d <= depth; d++)
					{
						if (((i - 1) / Pow2(depth - d)) % 2 == 0)
						{
							if (n)
								n = n->lhs;
							else
								break;
						}
						else
						{
							if (n)
								n = n->rhs;
							else
								break;
						}
					}

					if (n)
					{
						std::printf(n->ToString().c_str());
						no_children = false;
					}
					PrintSpaces(num_spaces);
				}

				std::printf("\n\n");

				depth++;
				num_spaces /= 2;
				it = Pow2(depth);
			}
			std::printf("\n");
		}
	}
}