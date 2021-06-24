#include "Operator.h"

#include <string>

namespace Compiler::Operator
{
    /*
    returns true if string is equal to an OP_STR, false otherwise
    */
    bool IsOperator(std::string str)
    {
        for (int i = 0; i < NUM_OPS; i++)
            if (STR[i] == str.c_str())
                return true;
        return false;
    }

    /*
        returns index of operator
        returns -1 if op not found
    */
    int GetOperatorIndex(std::string str, bool lhs, bool rhs)
    {
        for (int i = 0; i < NUM_OPS; i++)
            if (str.c_str() == STR[i] && lhs == LHS[i] && rhs == RHS[i])
                return i;
        return -1;
    }
}