#include "Flattener.h"

#include <iostream>

#include "../CompilerCore.h"


namespace Compiler {
    EvalLink* Flatten(Node* root)
    {
        EvalLink* head = nullptr, * prev = nullptr, * link = nullptr;
        do
        {
            Node* deepest = root, * parent = nullptr;
            bool isLhs = true;
            // find deepest (highest prec node)
            while (true)
            {
                if (deepest->lhs && !deepest->lhs->flattened)
                {
                    parent = deepest;
                    deepest = deepest->lhs;
                    isLhs = true;
                }
                else if (deepest->rhs && !deepest->rhs->flattened)
                {
                    parent = deepest;
                    deepest = deepest->rhs;
                    isLhs = false;
                }
                else
                    break;
            }

            // remove node and add to link
            if (deepest->type == Node::Type::OP)
                link = new EvalLink(isLhs ? EvalLink::Side::LHS : EvalLink::Side::RHS, deepest->lhs, deepest->rhs, deepest->op.index);
            else if (deepest->type == Node::Type::EXPR)
                link = new EvalLink(isLhs ? EvalLink::Side::LHS : EvalLink::Side::RHS, deepest->expr);

            deepest->flattened = true;

            if (!head)
            {
                head = link;
                prev = link;
            }
            else
            {
                prev->next = link;
                prev = link;
            }

        } while (!root->flattened);

        return head;
    }

	namespace Debug {
		void PrintLinkChain(EvalLink* head)
		{
			std::printf("Printing Link Chain:\n");

			EvalLink* current = head;
			while (current)
			{
				if (current->lhs)
					std::printf("L");
				if (current->rhs)
					std::printf("R");
				std::printf(" ");

				if (current->type == EvalLink::Type::EXPR)
					std::printf(current->expr.ToString().c_str());
				else if (current->type == EvalLink::Type::OP)
					std::printf(Operator::STR[current->op_index]);

				if (current->side == EvalLink::Side::LHS)
					std::printf(" L");
				else if (current->side == EvalLink::Side::RHS)
					std::printf(" R");

				current = current->next;
				if (current)
					std::printf("  ->  ");
			}
			std::printf("\n\n");
		}
	}
}