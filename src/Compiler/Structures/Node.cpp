#include "Node.h"

#include "../CompilerCore.h"

namespace Compiler {
    std::string Node::ToString() const
    {
        if (type == Type::OP)
            return Operator::STR[op.index];
        else
            return expr.ToString();
    }
}