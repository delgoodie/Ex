#include "Flattener.h"

#include <iostream>

#include "../CompilerCore.h"


namespace Compiler {
    EvalLink_Comp* Flatten(Node_Comp* root)
    {
        EvalLink_Comp* head = nullptr, * prev = nullptr, * link = nullptr;
        do
        {
            Node_Comp* deepest = root, * parent = nullptr;
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
            if (deepest->type == Node_Comp::Type::OP)
                link = new EvalLink_Comp(isLhs ? EvalLink_Comp::Side::LHS : EvalLink_Comp::Side::RHS, deepest->lhs, deepest->rhs, deepest->op.index);
            else if (deepest->type == Node_Comp::Type::EXPR)
                link = new EvalLink_Comp(isLhs ? EvalLink_Comp::Side::LHS : EvalLink_Comp::Side::RHS, deepest->expr);

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
		void PrintLinkChain(EvalLink_Comp* head)
		{
			std::printf("Printing Link Chain:\n");

			EvalLink_Comp* current = head;
			while (current)
			{
				if (current->lhs)
					std::printf("L");
				if (current->rhs)
					std::printf("R");
				std::printf(" ");

				if (current->type == EvalLink_Comp::Type::EXPR)
					std::printf(current->expr.ToString().c_str());
				else if (current->type == EvalLink_Comp::Type::OP)
					std::printf(Operator::STR[current->op.index]);

				if (current->side == EvalLink_Comp::Side::LHS)
					std::printf(" L");
				else if (current->side == EvalLink_Comp::Side::RHS)
					std::printf(" R");

				current = current->next;
				if (current)
					std::printf("  ->  ");
			}
			std::printf("\n\n");
		}
	}
}