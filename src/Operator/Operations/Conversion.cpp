#include "Conversion.h"

namespace Operator {
	Executor::Result Op_EqualTo(Executor::Expr* lhs, Executor::Expr* rhs, Executor::Context* context);

	namespace Conversion
	{
		size_t StringLength(Executor::StringLink* sl) {
			int i = 0;
			while (sl && sl->string[i % 5] != '\0') {
				i++;
				if (i > 0 && i % 5 == 0) sl = sl->next;
			}
			return i;
		}

		Executor::StringLink* StdStringToString(std::string string, Executor::Context* context)
		{
			Executor::StringLink* head = nullptr, *curr = context->StringHeap.Allocate(), *prev = nullptr;
			int length = string.length();

			for (int i = 0; i < length; i++) {
				if (i % 5 == 0 && i > 0) {
					if (!prev) head = curr;
					else prev->next = curr;
					curr->prev = prev;
					prev = curr;
					curr = context->StringHeap.Allocate();
				}
				curr->string[i % 5] = string[i];
			}

			if (prev) prev->next = curr;
			if (!head) head = curr;
			if (length % 5) curr->string[length % 5] = '\0';
			curr->next = nullptr;

			return head;
		}

		Executor::Expr NumberToString(Executor::Expr expr, Executor::Context* context)
		{
			Executor::StringLink* sl = StdStringToString(std::to_string(expr.number), context);
			return Executor::Expr(sl, StringLength(sl));
		}

		Executor::Expr StringToNumber(Executor::Expr expr)
		{
			return Executor::Expr(std::stod(expr.string.head->ToString()));
		}

		Executor::Expr NumberToBool(Executor::Expr expr)
		{
			return Executor::Expr(expr.number != 0);
		}

		Executor::Expr BoolToNumber(Executor::Expr expr)
		{
			return Executor::Expr(expr.boolean ? 1.0 : 0.0);
		}

		Executor::Expr StringToBool(Executor::Expr expr)
		{
			std::string string = expr.string.head->ToString();
			ex_boolean_t value = true;
			if (string.length() == 0)
				value = false;
			else if (string.length() == 5 && string.compare("false") == 0)
				value = false;
			else if (string.length() == 1 && string.compare("0") == 0)
				value = false;

			return Executor::Expr(value);
		}

		Executor::Expr BooleanToString(Executor::Expr expr, Executor::Context* context)
		{
			Executor::StringLink* sl = StdStringToString(expr.boolean ? "true" : "false", context);
			return Executor::Expr(sl, StringLength(sl));
		}

		Executor::Expr ObjectToBoolean(Executor::Expr expr)
		{
			//TODO: check if empty maybe?
			return Executor::Expr(true);
		}

		Executor::Expr ObjectToString(Executor::Expr expr, Executor::Context* context)
		{
			Executor::StringLink* sl = StdStringToString(expr.ToString(), context);
			return Executor::Expr(sl, StringLength(sl));
		}

		Executor::VarLink* FindVariable(Executor::Expr expr, Executor::VarLink* v_head, Executor::Context* context) {
			if (expr.type == Executor::Expr::Type::EX_VARIABLE) expr = Executor::Expr(expr.variable.name_head, StringLength(expr.variable.name_head));

			if (expr.type == Executor::Expr::Type::EX_STRING) {
				Executor::VarLink* vl = v_head;
				Executor::Expr vl_name(vl->name, StringLength(vl->name));

				while (vl && !Op_EqualTo(&expr, &vl_name, context).expr.boolean) {
					vl = vl->next;
					if(vl) 
						vl_name = Executor::Expr(vl->name, StringLength(vl->name));
				}
				return vl;
			}
			else throw "Can't find variable from expr";
		}

		Executor::Expr ConvertVariable(Executor::Expr expr, Executor::Context* context) {
			if (expr.type == Executor::Expr::Type::EX_VARIABLE && expr.variable.link) return expr.variable.link->expr;
			else return FindVariable(expr, context->top_frame->dot.variable.link->expr.object.v_head, context)->expr;
		}

		Executor::Expr Convert(Executor::Expr expr, Executor::Expr::Type type, Executor::Context* context)
		{
			if (expr.type == Executor::Expr::Type::EX_VARIABLE) expr = ConvertVariable(expr, context);
			if (expr.type == type)
				return expr;

			switch (expr.type)
			{
			case Executor::Expr::Type::EX_BOOLEAN:
				switch (type)
				{
				case Executor::Expr::Type::EX_NUMBER:
					return BoolToNumber(expr);
				case Executor::Expr::Type::EX_STRING:
					return BooleanToString(expr, context);
				default:
					std::printf("Can't convert boolean to type %d\n", (int)type);
					return Executor::Expr(nullptr);
				}
			case Executor::Expr::Type::EX_NUMBER:
				switch (type)
				{
				case Executor::Expr::Type::EX_BOOLEAN:
					return NumberToBool(expr);
				case Executor::Expr::Type::EX_STRING:
					return NumberToString(expr, context);
				default:
					std::printf("Can't convert number to type %d\n", (int)type);
					return Executor::Expr(nullptr);
				}
			case Executor::Expr::Type::EX_STRING:
				switch (type)
				{
				case Executor::Expr::Type::EX_BOOLEAN:
					return StringToBool(expr);
				case Executor::Expr::Type::EX_NUMBER:
					return StringToNumber(expr);
				default:
					std::printf("Can't convert string to type %d\n", (int)type);
					return Executor::Expr(nullptr);
				}
			case Executor::Expr::Type::EX_OBJECT:
				switch (type)
				{
				case Executor::Expr::Type::EX_BOOLEAN:
					return ObjectToBoolean(expr);
				case Executor::Expr::Type::EX_STRING:
					return ObjectToString(expr, context);
				default:
					std::printf("Can't convert Object to type %d\n", (int)type);
					return Executor::Expr(nullptr);
				}
			default:
				std::printf("Unconvertable Type %d\n", (int)expr.type);
				return Executor::Expr(nullptr);
			}
		}
	}
}