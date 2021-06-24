#include "Expander.h"

#include <iostream>

#include "../CompilerCore.h"

namespace Compiler {
    Node* Expand(std::vector<Node>& node_flat)
    {
        if (node_flat.size() == 0)
            std::printf("0 nodes\n");

        // Iterate over ops and expand by prec
        while (node_flat.size() > 1)
        {
            int mindex = -1;

            // find highest prec unexpanded op
            for (int i = 0; i < node_flat.size(); i++)
                if (node_flat[i].type == Node::Type::OP &&
                    !node_flat[i].expanded &&
                    (!Operator::LHS[node_flat[i].op.index] || i > 0 && node_flat[i - 1].expanded) &&
                    (!Operator::RHS[node_flat[i].op.index] || i + 1 < node_flat.size() && node_flat[i + 1].expanded) &&
                    (mindex == -1 || Operator::PREC[node_flat[i].op.index] < Operator::PREC[node_flat[mindex].op.index]))
                    mindex = i;

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
}