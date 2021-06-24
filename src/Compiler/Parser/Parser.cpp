#include "Parser.h"

#include <vector>
#include <string>
#include <iostream>

#include "../CompilerCore.h"

/*
The parser intakes a flat list of tokens

Then makes a pass converting each Token or group of tokens into Ex Types, Variables, and Ops, storing them in a flat list of Nodes

Then the Nodes are expanded by precedence to form a full Node Tree

Then the Node Tree is flattened into a linked list with instructions for execution

The final result is a linked list of the Link struct which is ready for evaluation and can be converted
into a bin equivalent so as to separate Lex & Parsing with Evaluation thus speeding up the program
*/

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

namespace Compiler
{

    /*
            Iterates over flat Token list Converts each Token or group of tokens into it's respective Type:
            * VAR  - variable
            * EXPR - Ex Type (EX_NUMBER, EX_STRING, EX_BOOLEAN, SOFT, SET, HARD), and an OP is any built in operator (+, -, ...)
            * OP   - built-in operator (+, -, ...)

            Stores Value in Node's:   void* value

            Temporarily uses lhs & rhs pointers as booleans
        */
    std::vector<Node> ConvertTokens(std::vector<Token>& tokens)
        {
            std::vector<Node> flatNodes;

            for (int i = 0; i < tokens.size(); i++)
            {
                if (tokens[i].type == Token::Type::NUM)
                    flatNodes.emplace_back(Expr((ex_number_t)std::stod(tokens[i].value)));
                else if (tokens[i].type == Token::Type::STR)
                    flatNodes.emplace_back(Expr(tokens[i].value));
                else if (tokens[i].type == Token::Type::VAR)
                    flatNodes.emplace_back(Expr(tokens[i].value, nullptr));
                else if (tokens[i].type == Token::Type::OP)
                {
                    // check if lhs and rhs are possible
                    int op_index = -1;

                    bool lhs = i > 0 && (tokens[i - 1].type != Token::Type::OP || !Operator::RHS[flatNodes.back().op.index]);
                    bool canRhs = Operator::GetOperatorIndex(tokens[i].value, lhs, true) != -1;
                    bool canNotRhs = Operator::GetOperatorIndex(tokens[i].value, lhs, false) != -1;

                    if (canRhs ^ canNotRhs)
                    {
                        op_index = Operator::GetOperatorIndex(tokens[i].value, lhs, canRhs);
                    }
                    else if (canRhs && canNotRhs)
                    {
                        bool rhs = i + 1 < tokens.size() &&
                            (tokens[i + 1].type == Token::Type::OP ||
                                (Operator::GetOperatorIndex(tokens[i + 1].value, false, true) != -1 ||
                                    Operator::GetOperatorIndex(tokens[i + 1].value, false, false) != -1));
                        op_index = Operator::GetOperatorIndex(tokens[i].value, lhs, rhs);
                    }
                    else
                    {
                        // TODO: invalid op error
                    }

                    flatNodes.emplace_back(op_index);
                }
                else if (tokens[i].type == Token::Type::PRE)
                {
                    int bracket_count = 1;
                    std::string bracket_str = tokens[i].value;
                    std::string close_bracket_str;
                    Object object;
                    //TODO: handle () and []
                    if (bracket_str.compare("{") == 0)
                        close_bracket_str = "}";
                    else if (bracket_str.compare("[") == 0)
                        close_bracket_str = "]";
                    else
                        close_bracket_str = ")";

                    int j = i + 1;
                    while (tokens[j].type != Token::Type::PRE || tokens[j].value.compare(bracket_str) != 0 || bracket_count != 0)
                    {
                        // Bracket Count Update
                        if (tokens[j].type == Token::Type::PRE)
                        {
                            if (tokens[j].value.compare(bracket_str) == 0)
                                bracket_count++;
                            else if (tokens[j].value.compare(close_bracket_str) == 0)
                                bracket_count--;
                        }
                        j++;
                    }

                    // i = index of {, j = index of }
                    std::vector<Token>::const_iterator first = tokens.begin() + i + 1;
                    std::vector<Token>::const_iterator last = tokens.begin() + j;
                    std::vector<Token> token_flat(first, last);

                    object.node_flat = ConvertTokens(token_flat);
                    object.node_tree = BuildNodeTree(object.node_flat);
                    object.link_head = FlattenNodeTree(object.node_tree);

                    flatNodes.emplace_back(Expr(object));
                    // Advance i to j (which will be } but for loop increments i as well)
                    i = j;
                }
            }

            // * Easy way to view op indicies
            // int op_indexes[20];
            // for (int i = 0; i < flatNodes.size(); i++)
            //     op_indexes[i] = flatNodes[i].op.index;

            return flatNodes;
        }

   namespace Debug
    {
        bool Enabled = false;
        void PrintNodeFlat(std::vector<Node>& flat)
        {
            if (!Enabled)
                return;
            std::printf("Printing Flat Node List:\n");
            for (int i = 0; i < flat.size(); i++)
            {
                std::printf("%s ", flat[i].ToString().c_str());
            }
            std::printf("\n");
        }

        void PrintNodeTree(Node* root)
        {
            if (!Enabled)
                return;
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

        void PrintLinkChain(EvalLink* head)
        {
            if (!Enabled)
                return;
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
            std::printf("\n");
        }
    }

    EvalLink* Exec(std::vector<Token>& tokens)
    {
        std::vector<Node> flatNodes = Pipeline::ConvertTokens(tokens);
        Debug::PrintNodeFlat(flatNodes);

        Node* root = Pipeline::BuildNodeTree(flatNodes);
        Debug::PrintNodeTree(root);

        EvalLink* head = Pipeline::FlattenNodeTree(root);
        Debug::PrintLinkChain(head);

        return head;
    }
}