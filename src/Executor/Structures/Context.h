#pragma once

#include "../Core.h"

#include "Stack.h"
#include "Heap.h"
#include "Frame.h"

namespace Executor {
	struct Expr;
	struct EvalLink;
	struct VarLink;
	struct ListLink;
	struct StringLink;

	class Context
	{
	private:
		Stack<Frame, EX_FRAME_STACK_SIZE> FrameStack;
	public:
		Frame* top_frame;

		Stack<Expr, EX_EXPR_STACK_SIZE> ExprStack;
		Heap<EvalLink, EX_EVAL_HEAP_SIZE> EvalHeap;
		Heap<VarLink, EX_VAR_HEAP_SIZE> VarHeap;
		Heap<ListLink, EX_LIST_HEAP_SIZE> ListHeap;
		Heap<StringLink, EX_STRING_HEAP_SIZE> StringHeap;

		void PushFrame(Frame frame) {
			FrameStack.BottomPush(frame);
			top_frame = FrameStack.PeekBottom(0);
		}

		void PopFrame() {
			FrameStack.BottomPop();
			top_frame = FrameStack.PeekBottom(0);
		}

		Frame* PeekFrame(int index) {
			return FrameStack.PeekBottom(index);
		}
	};
}