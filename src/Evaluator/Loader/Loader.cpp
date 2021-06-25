#include "Loader.h"

namespace Evaluator {

	static StringLink* LoadString(char* string, Context* context) {
		StringLink* head = nullptr, * curr, * prev = nullptr;
		int length = strlen(string);

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
		EvalLink* head = nullptr, *prev = nullptr, *curr = nullptr;
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
			if (!curr->prev) head = curr;
			prev->next = curr;
			prev = curr;

			link = EvalLink(*ptr++);
		}
	}

	Context* Load(Blob blob) {
		
		Context* context = new Context();

		EvalLink* entry = LoadObject(blob.data, context);
	}
}