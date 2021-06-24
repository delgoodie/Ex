#pragma once

#include <vector>

#include "../CompilerCore.h"

namespace Compiler {
    struct Object
    {
        std::vector<Node> node_flat;
        Node* node_tree;
        EvalLink* link_head;
        Object() {}
        Object(std::vector<Node> nf) : node_flat(nf), node_tree(nullptr), link_head(nullptr) {}
    };
}
