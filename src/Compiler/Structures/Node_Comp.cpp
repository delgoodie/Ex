#include "Node_Comp.h"

#include "../CompilerCore.h"

namespace Compiler {
    std::string Node_Comp::ToString() const
    {
        if (type == Type::OP)
            return Operator::STR[op.index];
        else
            return expr.ToString();
    }
}