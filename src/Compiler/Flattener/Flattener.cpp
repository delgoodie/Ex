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
            bool isLhs = true, isParentLhs = true;
            // find deepest (highest prec node)
            while (true)
            {
                if (deepest->lhs && !deepest->lhs->flattened)
                {
                    parent = deepest;
                    isParentLhs = isLhs;
                    deepest = deepest->lhs;
                    isLhs = true;
                }
                else if (deepest->rhs && !deepest->rhs->flattened)
                {
                    parent = deepest;
                    isParentLhs = isLhs;
                    deepest = deepest->rhs;
                    isLhs = false;
                }
                else
                    break;
            }

            // flatten node and add to chain
            if (deepest->type == Node_Comp::Type::OP) {
                if (Operator::POS[deepest->op.index] == 1)
                    link = new EvalLink_Comp(isLhs ? EvalLink_Comp::Side::LHS : EvalLink_Comp::Side::RHS, deepest->lhs, deepest->rhs, deepest->op.index);
                else {
                    deepest->flattened = true;
                    continue;
                }
            }
            else if (deepest->type == Node_Comp::Type::EXPR) {
                link = new EvalLink_Comp(isLhs ? EvalLink_Comp::Side::LHS : EvalLink_Comp::Side::RHS, deepest->expr);
            }

            if (parent && parent->type == Node_Comp::Type::OP && (isLhs && Operator::POS[parent->op.index] == -1 || !isLhs && Operator::POS[parent->op.index] == 0)) {
                EvalLink_Comp* op_link = new EvalLink_Comp(isParentLhs ? EvalLink_Comp::Side::LHS : EvalLink_Comp::Side::RHS, parent->lhs, parent->rhs, parent->op.index);
                if (!prev) head = op_link;
                else prev->next = op_link;
                prev = op_link;
            }


            deepest->flattened = true;

            if (!prev) head = link;
            else prev->next = link;
            prev = link;
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