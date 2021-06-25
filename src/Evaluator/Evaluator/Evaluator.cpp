#include "Evaluator.h"

#include "../Operator/Operator.h"

namespace Evaluator {
    Expr Evaluate(EvalLink* head, Context* context)
    {
        EvalLink* it = head;
        // TODO: flush out call stack, currently just obj stack, need to make Frame?? Struct to hold object, index, stack lhs start, stack rhs start (for delete on return)
        while (it)
        {
            if (it->TypeFlag()) // Op
            {
                Operator::Result result = Operator::FUNC[it->op.index](it->LHSFlag() ? context->ExprStack.BottomPop() : nullptr, it->RHSFlag() ? context->ExprStack.TopPop() : nullptr, context);
                
                if (result.ErrorFlag()) {
                    // Error handling
                }
                else if (result.ExitFlag()) {
                    // TODO: Somehow clear stack of temp vals using context
                    context->ExprStack.BottomPush(result.expr);
                    break;
                }
                else if (result.JumpFlag()) {
                    if (it->op.jump > 0) for (int i = 0; i < it->op.jump; i++) it = it->next;
                    else for (int i = 0; i > it->op.jump; i--) it = it->prev;
                }
                else {
                    if (it->SideFlag()) // Lhs
                        context->ExprStack.BottomPush(result.expr);
                    else // Rhs
                        context->ExprStack.TopPush(result.expr);
                }
            }
            else // Expr
            {
            if (it->SideFlag()) // Lhs
                context->ExprStack.BottomPush(it->expr);
            else // Rhs
                context->ExprStack.TopPush(it->expr);
            }
            
            it = it->next;
        }
    }
}