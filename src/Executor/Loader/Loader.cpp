#include "Loader.h"

#include <iostream>
#include <sstream>

namespace Executor {

	static StringLink* LoadString(char* string, Context* context) {
		StringLink* head = nullptr, * curr, * prev = nullptr;
		int length = (int)strlen(string);

		for (int i = 0; i < length; i += 5) {
			char strbuf[5];
			int end = -1;
			for (int j = 0; j < 5; j++) {
				if (i + j < length) end = j;
				if (end == -1) strbuf[j] = string[i + j];
				else strbuf[j] = '\0';
			}

			curr = context->StringHeap.Allocate(StringLink(prev, strbuf));
			if (!head) head = curr;
			prev->next = curr;
			prev = curr;
		}

		return head;
	}

	static EvalLink* LoadObject(unsigned char* ptr, Context* context) {
		EvalLink *head = nullptr, *prev = nullptr, *curr = nullptr;
		EvalLink link(*(ptr++));

		while (!link.NullFlag()) {
			link.prev = prev;

			if (link.NullFlag()); // Null
			else if (link.TypeFlag()) // Op
			{
				link.op.index = *(int*)ptr;
				ptr += sizeof(int);
				link.op.jump = *(int*)ptr;
				ptr += sizeof(int);
			}
			else // Expr
			{
				link.expr.type = (Expr::Type)*(ptr++); // Expr Type
				switch (link.expr.type) {
				case Expr::Type::EX_NULL:
					break;
				case Expr::Type::EX_BOOLEAN:
					link.expr.boolean = *(ptr++);
					break;
				case Expr::Type::EX_NUMBER:
					link.expr.number = *(double*)ptr;
					ptr += sizeof(double);
					break;
				case Expr::Type::EX_STRING:
					link.expr.string.head = LoadString((char *)ptr, context);
					link.expr.string.length = strlen((char *)ptr);
					ptr += link.expr.string.length + 1;
					break;
				case Expr::Type::EX_VARIABLE:
					link.expr.variable.name_head = LoadString((char*)ptr, context);
					link.expr.variable.ptr = nullptr;
					ptr += strlen((char*)ptr);
					break;
				case Expr::Type::EX_OBJECT:
					size_t obj_size = *(size_t*)ptr;
					ptr += sizeof(size_t);
					link.expr.object.e_head = LoadObject(ptr, context);
					link.expr.object.v_head = nullptr;
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

		return head;
	}

	Context* Load(Blob blob) {
		Context* context = new Context();

		Frame frame;
		frame.e_head = LoadObject(blob.data, context);
		frame.e_curr = frame.e_head;
		frame.e_index = 0;
		frame.lhs_size = 0;
		frame.rhs_size = 0;
		frame.v_head = nullptr;
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
					std::printf("%s  ", el.TypeFlag() ? "OP" : "EXPR");
					if (el.TypeFlag()) {
						std::printf("%d  %s %s", el.op.index, el.LHSFlag() ? "L" : "", el.RHSFlag() ? "R" : "");
					}
					else {
						std::printf("T: %d  ", el.expr.type);
						switch (el.expr.type) {
						case Expr::Type::EX_NULL:
							std::printf("NULL");
							break;
						case Expr::Type::EX_BOOLEAN:
							std::printf(el.expr.boolean ? "true" : "false");
							break;
						case Expr::Type::EX_NUMBER:
							std::printf("%g", el.expr.number);
							break;
						case Expr::Type::EX_STRING:
							std::printf("%p %d", el.expr.string.head, (int)el.expr.string.length);
							break;
						case Expr::Type::EX_VARIABLE:
							std::printf("%p %p", el.expr.variable.name_head, el.expr.variable.ptr);
							break;
						case Expr::Type::EX_OBJECT:
							std::printf("%p %p", el.expr.object.e_head, el.expr.object.v_head);
							break;
						}
					}
					std::printf("    %p\n\n", el.next);
				}
			}

		}
	}
}