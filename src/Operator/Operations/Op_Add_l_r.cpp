#include "../Executor/ExecutorCore.h"

#include <sstream>

#include "Conversion.h"

namespace Operator {
	Executor::Result Op_Add_l_r (const Executor::Expr& lhs, const Executor::Expr& rhs,  Executor::Context* context) {
        // String Concat
        if (lhs.type == Executor::Expr::Type::EX_STRING || rhs.type == Executor::Expr::Type::EX_STRING)
        {
            Executor::Expr c_lhs = Conversion::Convert(lhs, Executor::Expr::Type::EX_STRING);
            Executor::Expr c_rhs = Conversion::Convert(rhs, Executor::Expr::Type::EX_STRING);

            std::string sum = c_lhs.string.head->ToString() + c_rhs.string.head->ToString();

            Executor::StringLink* head = nullptr, * curr = context->StringHeap.Allocate(), * prev = nullptr;
            int length = sum.length();

            for (int i = 0; i < length; i++) {
                if (i % 5 == 0 && i > 0) {
                    if (!prev) head = curr;
                    else prev->next = curr;
                    curr->prev = prev;
                    prev = curr;
                    curr = context->StringHeap.Allocate();
                }
                curr->string[i % 5] = sum[i];
            }

            if (prev) prev->next = curr;
            if (!head) head = curr;
            if (length % 5) curr->string[length % 5] = '\0';
            curr->next = nullptr;

            return Executor::Result(Executor::Expr(head, length));
        }
        else if (lhs.type == Executor::Expr::Type::EX_NUMBER || rhs.type == Executor::Expr::Type::EX_NUMBER) // Numerical Addition
        {
            Executor::Expr c_lhs = Conversion::Convert(lhs, Executor::Expr::Type::EX_NUMBER);
            Executor::Expr c_rhs = Conversion::Convert(rhs, Executor::Expr::Type::EX_NUMBER);
            return Executor::Result(Executor::Expr(c_lhs.number + c_rhs.number));
        }
        else if (lhs.type == Executor::Expr::Type::EX_BOOLEAN && rhs.type == Executor::Expr::Type::EX_BOOLEAN)
        {
            return Executor::Result(Executor::Expr(lhs.boolean || rhs.boolean));
        }
        else
        {
            // unsuported value
            return Executor::Result(Executor::Expr(nullptr));
        }
	}
}