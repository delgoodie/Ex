#include "Evaluator.h"

#include "../Operator/Operator.h"


// ^ op just adds new stack, and Evaluate only operates on top of stack, but I have a local ptr so I need to maybe point to pointer to top of stack?

namespace Executor {
    Expr Evaluate(Context* context)
    {
        while(context->top_frame)
        {
            Frame::ReturnSide returnSide = context->top_frame->side;

            while (context->top_frame->e_curr) {
            
                if (context->top_frame->e_curr->TypeFlag()) // Op
                {
                    Operator::Result result = Operator::FUNC[context->top_frame->e_curr->op.index](context->top_frame->e_curr->LHSFlag() && context->top_frame->lhs_size-- ? context->ExprStack.BottomPop() : nullptr, context->top_frame->e_curr->RHSFlag() && context->top_frame->rhs_size-- ? context->ExprStack.TopPop() : nullptr, context);
                
                    if (result.ErrorFlag()) {
                        // Error handling
                    }
                    else if (result.ExitFlag()) {
                        context->ExprStack.BottomPush(result.ReturnFlag() ? result.expr : Expr(nullptr));
                        context->top_frame->lhs_size++;
                        break;
                    }
                    else if (result.JumpFlag()) {
                        if (result.ReturnFlag()) {
                            if (context->top_frame->e_curr->SideFlag()) context->ExprStack.BottomPush(result.expr); // Lhs
                            else context->ExprStack.TopPush(result.expr); // Rhs
                        }
                        int jump = context->top_frame->e_curr->op.jump;
                        for (int i = 0; i < abs(jump); i++) context->top_frame->e_curr = jump > 0 ? context->top_frame->e_curr->next : context->top_frame->e_curr->prev;
                        continue;
                    }
                    else {
                        if (result.ReturnFlag()) {
                            if (context->top_frame->e_curr->SideFlag()) {
                                context->ExprStack.BottomPush(result.expr); // Lhs
                                context->top_frame->lhs_size++;
                            }
                            else {
                                context->ExprStack.TopPush(result.expr); // Rhs
                                context->top_frame->rhs_size++;
                            }
                        }
                    }
                }
                else // Expr
                {
                    if (context->top_frame->e_curr->SideFlag()) {
                        context->ExprStack.BottomPush(context->top_frame->e_curr->expr);
                        context->top_frame->lhs_size++;
                    }
                    else {
                        context->ExprStack.TopPush(context->top_frame->e_curr->expr);
                        context->top_frame->rhs_size++;
                    }
                }
            
                context->top_frame->e_curr = context->top_frame->e_curr->next;
            }

            Expr returnExpr = context->ExprStack.BottomPop();
            context->top_frame->lhs_size--;

            while (context->top_frame->lhs_size-- > 0) context->ExprStack.BottomPop();
            while (context->top_frame->rhs_size-- > 0) context->ExprStack.TopPop();

            context->PopFrame();

            if (context->top_frame) {
                if (returnSide == Frame::ReturnSide::LHS) {
                    context->ExprStack.BottomPush(returnExpr);
                    context->top_frame->lhs_size++;
                }
                else {
                    context->ExprStack.TopPush(returnExpr);
                    context->top_frame->rhs_size++;
                }
            }
            else {
                return returnExpr;
            }
        }
        return Expr(nullptr);
    }
}