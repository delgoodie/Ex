#include "Evaluator.h"

#include <string>

#include "../../Operator/Operator.h"


// ^ op just adds new stack, and Evaluate only operates on top of stack, but I have a local ptr so I need to maybe point to pointer to top of stack?

namespace Executor {
	Expr Evaluate(Context* context)
	{
		while (context->top_frame)
		{
			while (context->top_frame->e_curr) {
				bool frame_switch = false;

				if (context->top_frame->e_curr->TypeFlag()) // Op
				{
					Expr* lhs_expr = nullptr;
					Expr* rhs_expr = nullptr;

					if (context->top_frame->e_curr->LHSFlag()) {
						lhs_expr = context->ExprStack.PeekBottom(0);
						context->top_frame->lhs_size--;
					}
					if (context->top_frame->e_curr->RHSFlag()) {
						rhs_expr = context->ExprStack.PeekTop(0);
						context->top_frame->rhs_size--;
					}

#ifdef _DEBUG
					const char* op_str = Operator::STR[context->top_frame->e_curr->op.index];
					std::string lhs_str = context->top_frame->e_curr->LHSFlag() ? "<- L " + lhs_expr->ToString() : "";
					std::string rhs_str = context->top_frame->e_curr->RHSFlag() ? "<- R " + rhs_expr->ToString() : "";
					std::printf("%s  %s  %s\n", op_str, lhs_str.c_str(), rhs_str.c_str());
#endif

					Result result = Operator::FUNC[context->top_frame->e_curr->op.index](lhs_expr, rhs_expr, context);
					if (lhs_expr) context->ExprStack.BottomPop();
					if (rhs_expr) context->ExprStack.TopPop();

					if (result.ErrorFlag()) {
						// Error handling
						std::printf("Handle Error");
						break;
					}

					if (result.ExitFlag()) {
#ifdef _DEBUG
						std::printf("%s  ->  L\n", result.expr.ToString().c_str());
#endif
						context->ExprStack.BottomPush(result.ReturnFlag() ? result.expr : Expr(nullptr));
						context->top_frame->lhs_size++;
						break;
					}

					if (result.ReturnFlag()) {
#ifdef _DEBUG
						std::printf("%s  ->  %s\n", result.expr.ToString().c_str(), context->top_frame->e_curr->SideFlag() ? "L" : "R");
#endif
						if (context->top_frame->e_curr->SideFlag()) {
							context->ExprStack.BottomPush(result.expr); // Lhs
							context->top_frame->lhs_size++;
						}
						else {
							context->ExprStack.TopPush(result.expr); // Rhs
							context->top_frame->rhs_size++;
						}
					}

					if (result.JumpFlag()) {
						int jump = context->top_frame->e_curr->op.jump;
						for (int i = 0; i < abs(jump); i++) context->top_frame->e_curr = jump > 0 ? context->top_frame->e_curr->next : context->top_frame->e_curr->prev;
						continue;
					}

					if (result.FrameSwitchFlag()) {
						frame_switch = true;
					}
				}
				else // Expr
				{
					std::printf("%s  ->  %s\n", context->top_frame->e_curr->expr.ToString().c_str(), context->top_frame->e_curr->SideFlag() ? "L" : "R");
					if (context->top_frame->e_curr->SideFlag()) {
						context->ExprStack.BottomPush(context->top_frame->e_curr->expr);
						context->top_frame->lhs_size++;
					}
					else {
						context->ExprStack.TopPush(context->top_frame->e_curr->expr);
						context->top_frame->rhs_size++;
					}
				}

				if (!frame_switch)
					context->top_frame->e_curr = context->top_frame->e_curr->next;
			}


			Expr returnExpr = context->ExprStack.BottomPop();
			context->top_frame->lhs_size--;
			if (returnExpr.type == Expr::Type::EX_VARIABLE && !returnExpr.variable.link) returnExpr.variable.link = Operator::Conversion::FindVariable(returnExpr, context->top_frame->dot.variable.link->expr.object.v_head, context);

#ifdef _DEBUG
			std::printf("(return)  <-  L %s\n", returnExpr.ToString().c_str());
#endif

			while (context->top_frame->lhs_size-- > 0) {
				Expr l_removed_expr = context->ExprStack.BottomPop();
#ifdef _DEBUG
				std::printf("(discard)  <-  L %s\n", l_removed_expr.ToString().c_str());
#endif
			}
			while (context->top_frame->rhs_size-- > 0) {
				Expr r_removed_expr = context->ExprStack.TopPop();
#ifdef _DEBUG
				std::printf("(discard)  <-  R %s\n", r_removed_expr.ToString().c_str());
#endif
			}

			Frame::ReturnSide returnSide = context->top_frame->side;

			context->PopFrame();

			if (context->top_frame) {
				if (returnSide == Frame::ReturnSide::LHS) {
					context->ExprStack.BottomPush(returnExpr);
					context->top_frame->lhs_size++;
#ifdef _DEBUG
					std::printf("%s  ->  L\n", returnExpr.ToString().c_str());
#endif
				}
				else {
					context->ExprStack.TopPush(returnExpr);
					context->top_frame->rhs_size++;
#ifdef _DEBUG
					std::printf("%s  ->  R\n", returnExpr.ToString().c_str());
#endif
				}
			}
			else {
				return returnExpr;
			}
		}
		return Expr(nullptr);
	}
}