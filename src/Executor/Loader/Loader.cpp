#include "Loader.h"

#include <iostream>
#include <sstream>

#include "../../Operator/Operator.h"

namespace Executor {

	static StringLink* LoadString(char* string, Context* context) {
		std::string stdstr = std::string(string);
		return Operator::Conversion::StdStringToString(stdstr, context);
	}

	static Object LoadObject(unsigned char* ptr, Context* context) {
		EvalLink* head = nullptr, *prev = nullptr, *curr = nullptr;
		EvalLink link(*(ptr++));

		while (!link.NullFlag()) {
			link.prev = prev;

			if (link.NullFlag()); // Null
			else if (link.TypeFlag()) // Op
			{
				link.op.index = *reinterpret_cast<int*>(ptr);
				ptr += sizeof(int);
				link.op.jump = *reinterpret_cast<int*>(ptr);
				ptr += sizeof(int);
			}
			else  // Expr
			{
				link.expr.type = (Expr::Type) * (ptr++); // Expr Type
				switch (link.expr.type) {
				case Expr::Type::EX_NULL:
					break;
				case Expr::Type::EX_BOOLEAN:
					link.expr.boolean = *(ptr++);
					break;
				case Expr::Type::EX_NUMBER:
					link.expr.number = *reinterpret_cast<double*>(ptr);
					ptr += sizeof(double);
					break;
				case Expr::Type::EX_STRING:
					link.expr.string.head = LoadString(reinterpret_cast<char*>(ptr), context);
					link.expr.string.length = strlen(reinterpret_cast<char*>(ptr));
					ptr += link.expr.string.length + 1;
					break;
				case Expr::Type::EX_VARIABLE:
					link.expr.variable.name_head = LoadString(reinterpret_cast<char*>(ptr), context);
					link.expr.variable.link = nullptr;
					ptr += strlen(reinterpret_cast<char*>(ptr)) + 1;
					break;
				case Expr::Type::EX_OBJECT:
					size_t obj_size = *reinterpret_cast<size_t*>(ptr);
					ptr += sizeof(size_t);
					link.expr.object = LoadObject(ptr, context);
					ptr += obj_size;
					break;
				}
			}

			curr = context->EvalHeap.Allocate(link);
			if (!prev) head = curr;
			else prev->next = curr;
			prev = curr;

			link = EvalLink(*ptr++);
		}

		curr->next = nullptr;

		return { head, nullptr };
	}

	Context* Load(Blob blob) {
		Context* context = new Context();

		Frame frame;

		VarLink* vl = context->VarHeap.Allocate();
		vl->prev = nullptr;
		vl->next = nullptr;
		vl->expr = Expr(LoadObject(blob.data, context));

		frame.dot = Expr(nullptr, vl);
		frame.e_curr = frame.dot.variable.link->expr.object.e_head;
		frame.e_index = 0;
		frame.lhs_size = 0;
		frame.rhs_size = 0;
		frame.side = Frame::ReturnSide::LHS;

		context->PushFrame(frame);

		return context;
	}

	namespace Debug {
		void PrintContext(Context* context) {
			std::printf("Printing Context:\n\n");

			std::printf("EvalLink Heap:\n\n");

			for (int i = 0; i < EX_EVAL_HEAP_SIZE; i++) {
				if (!context->EvalHeap.IsFree(i))
				{
					EvalLink el = context->EvalHeap.Begin()[i];
					std::printf("%p\n", &context->EvalHeap.Begin()[i]);
					std::printf("%p    ", el.prev);
					std::printf("%s  ", el.SideFlag() ? "L" : "R");
					if (el.TypeFlag()) {
						std::printf("OP  %s  %s %s", Operator::STR[el.op.index], el.LHSFlag() ? "L" : "", el.RHSFlag() ? "R" : "");
					}
					else {
						std::printf("%s  %s", Expr::TypeToString(el.expr.type).c_str(), el.expr.ToString().c_str());
					}
					std::printf("    %p\n\n", el.next);
				}
			}

		}
	}
}