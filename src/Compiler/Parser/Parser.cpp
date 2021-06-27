#include "Parser.h"

#include <vector>
#include <string>
#include <iostream>

#include "../CompilerCore.h"

#include "../Expander/Expander.h"
#include "../Flattener/Flattener.h"

/*
The parser intakes a flat list of tokens

Then makes a pass converting each Token or group of tokens into Ex Types, Variables, and Ops, storing them in a flat list of Nodes

Then the Nodes are expanded by precedence to form a full Node Tree

Then the Node Tree is flattened into a linked list with instructions for execution

The final result is a linked list of the Link struct which is ready for evaluation and can be converted
into a bin equivalent so as to separate Lex & Parsing with Evaluation thus speeding up the program
*/

namespace Compiler
{

	static int GetOperatorIndex(std::string str, bool lhs, bool rhs)
	{
		for (int i = 0; i < NUM_OPS; i++)
			if (lhs == Operator::LHS[i] && rhs == Operator::RHS[i] && str.length() == strlen(Operator::STR[i]))
			{
				bool f = true;
				for (int j = 0; j < str.length(); j++)
					if (Operator::STR[i][j] != str[j]) f = false;
				if (f) return i;
			}
		return -1;
	}

    /*
            Iterates over flat Token list Converts each Token or group of tokens into it's respective Type:
            * VAR  - variable
            * EXPR - Ex Type (EX_NUMBER, EX_STRING, EX_BOOLEAN, SOFT, SET, HARD), and an OP is any built in operator (+, -, ...)
            * OP   - built-in operator (+, -, ...)

            Stores Value in Node's:   void* value

            Temporarily uses lhs & rhs pointers as booleans
        */
    std::vector<Node_Comp> Parse(const std::vector<Token_Comp>& tokens)
        {
            std::vector<Node_Comp> flatNodes;

            for (int i = 0; i < tokens.size(); i++)
            {
				if (tokens[i].type == Token_Comp::Type::NUM)
                    flatNodes.emplace_back(Expr_Comp((ex_number_t)std::stod(tokens[i].value)));
				else if (tokens[i].type == Token_Comp::Type::STR)
                    flatNodes.emplace_back(Expr_Comp(tokens[i].value));
				else if (tokens[i].type == Token_Comp::Type::VAR)
                    flatNodes.emplace_back(Expr_Comp(tokens[i].value, nullptr));
                else if (tokens[i].type == Token_Comp::Type::OP)
                {
                    // check if lhs and rhs are possible
                    int op_index = -1;

                    bool lhs = i > 0 && (tokens[i - 1].type != Token_Comp::Type::OP || !Operator::RHS[flatNodes.back().op.index]);
                    bool canRhs = GetOperatorIndex(tokens[i].value, lhs, true) != -1;
                    bool canNotRhs = GetOperatorIndex(tokens[i].value, lhs, false) != -1;

                    if (canRhs ^ canNotRhs)
                    {
                        op_index = GetOperatorIndex(tokens[i].value, lhs, canRhs);
                    }
                    else if (canRhs && canNotRhs)
                    {
                        bool rhs = i + 1 < tokens.size() &&
                            (tokens[i + 1].type == Token_Comp::Type::OP ||
                                (GetOperatorIndex(tokens[i + 1].value, false, true) != -1 ||
                                    GetOperatorIndex(tokens[i + 1].value, false, false) != -1));
                        op_index = GetOperatorIndex(tokens[i].value, lhs, rhs);
                    }
                    else
                    {
                        // TODO: invalid op error
                    }

                    flatNodes.emplace_back(op_index);
                }
                else if (tokens[i].type == Token_Comp::Type::PRE)
                {
                    int bracket_count = 1;
                    std::string bracket_str = tokens[i].value;
                    std::string close_bracket_str;
                    //TODO: handle () and []
                    if (bracket_str.compare("{") == 0)
                        close_bracket_str = "}";
                    else if (bracket_str.compare("[") == 0)
                        close_bracket_str = "]";
                    else
                        close_bracket_str = ")";

                    int j = i + 1;
                    while (bracket_count != 0)
                    {
                        // Bracket Count Update
                        if (tokens[j].type == Token_Comp::Type::PRE)
                        {
                            if (tokens[j].value.compare(bracket_str) == 0)
                                bracket_count++;
                            else if (tokens[j].value.compare(close_bracket_str) == 0)
                                bracket_count--;
                        }
                        j++;
                    }

                    // i = index of {, j = index after }
                    std::vector<Token_Comp>::const_iterator first = tokens.begin() + i + 1;
                    std::vector<Token_Comp>::const_iterator last = tokens.begin() + j - 1;
                    std::vector<Token_Comp> token_flat(first, last);

					std::vector<Node_Comp> node_flat = Parse(token_flat);
                    Node_Comp* node_tree = Expand(node_flat);
                    EvalLink_Comp* object = Flatten(node_tree);

                    flatNodes.emplace_back(Expr_Comp(object));

                    // Advance i to j - 1 (which will be } but for loop increments i as well)
                    i = j - 1;
                }
            }

            return flatNodes;
        }

   namespace Debug
    {
        void PrintNodeFlat(const std::vector<Node_Comp>& node_flat)
        {
            std::printf("Printing Flat Node List:\n");
            for (int i = 0; i < node_flat.size(); i++)
                std::printf("%s ", node_flat[i].ToString().c_str());
            std::printf("\n\n");
        }
    }
}