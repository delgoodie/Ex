#include "Node.h"

#include "../CompilerCore.h"

namespace Compiler {

    Node::Node(const Node& node) {
        type = node.type;
        if (type == Type::EXPR) expr = node.expr;
        else op = node.op;
        lhs = node.lhs;
        rhs = node.rhs;
        expanded = node.expanded;
        flattened = node.flattened;
    }

    std::string Node::ToString()
    {
        if (type == Type::OP)
            return Operator::STR[op.index];
        else
            return expr.ToString();
    }
}