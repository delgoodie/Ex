#pragma once

#include <vector>

#include "../CompilerCore.h"

namespace Compiler::Parser
{
    namespace Pipeline
    {
        std::vector<Node> ConvertTokens(std::vector<Token>& tokens);
        Node* BuildNodeTree(std::vector<Node>& flatNodes);
        EvalLink* FlattenNodeTree(Node* root);
    }
    namespace Debug
    {
        extern bool Enabled;
    }
    EvalLink* Exec(std::vector<Token>& tokens);
}