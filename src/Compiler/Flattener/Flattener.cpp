#include "Flattener.h"

#include <iostream>

#include "../CompilerCore.h"


namespace Compiler {

	static int TreeSize(Node_Comp* root) {
		int size = 1;
		if (root->rhs) size += TreeSize(root->rhs);
		if (root->lhs) size += TreeSize(root->lhs);
		return size;
	}

	EvalLink_Comp* Flatten(Node_Comp* root)
	{
		EvalLink_Comp* head = nullptr, * prev = nullptr, * link = nullptr;
		do
		{
			Node_Comp* deepest = root, * parent = nullptr;
			// find deepest (highest prec node)
			while (true)
			{
				if (deepest->type == Node_Comp::Type::OP && Operator::POS[deepest->op.index] == -1 && !deepest->part_flattened) break;
				else if (deepest->type == Node_Comp::Type::OP && Operator::POS[deepest->op.index] == 0 && !deepest->part_flattened && deepest->lhs->flattened) break;

				if (deepest->lhs && !deepest->lhs->flattened) {
					parent = deepest;
					deepest = deepest->lhs;
				}
				else if (deepest->rhs && !deepest->rhs->flattened)
				{
					parent = deepest;
					deepest = deepest->rhs;
				}
				else break;
			}
			// Check parent op for non 1 pos
			if (parent && parent->type == Node_Comp::Type::OP && Operator::POS[parent->op.index] != 1 && deepest->side == Node_Comp::Side::RHS)
				deepest->side = parent->side;

			// flatten node and add to chain
			if (deepest->type == Node_Comp::Type::OP) {
				if (Operator::POS[deepest->op.index] == 1) {
					link = new EvalLink_Comp(deepest->side == Node_Comp::Side::LHS ? EvalLink_Comp::Side::LHS : EvalLink_Comp::Side::RHS, deepest->lhs, deepest->rhs, deepest->op.index);
					deepest->flattened = true;
				}
				else {
					if (!deepest->part_flattened) {
						if (Operator::POS[deepest->op.index] == -1)
							link = new EvalLink_Comp(deepest->side == Node_Comp::Side::LHS ? EvalLink_Comp::Side::LHS : EvalLink_Comp::Side::RHS, false, false, deepest->op.index, TreeSize(deepest->lhs) + 1);
						else
							link = new EvalLink_Comp(deepest->side == Node_Comp::Side::LHS ? EvalLink_Comp::Side::LHS : EvalLink_Comp::Side::RHS, deepest->lhs, false, deepest->op.index, TreeSize(deepest->rhs) + 1);
						deepest->part_flattened = true;
					}
					else {
						deepest->flattened = true;
						continue;
					}
				}
			}
			else if (deepest->type == Node_Comp::Type::EXPR) {
				link = new EvalLink_Comp(deepest->side == Node_Comp::Side::LHS ? EvalLink_Comp::Side::LHS : EvalLink_Comp::Side::RHS, deepest->expr);
				deepest->flattened = true;
			}

			// Link Chain
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