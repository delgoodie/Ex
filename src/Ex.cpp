#include <iostream>

#include "Core.h"
#include "Compiler/Compiler.h"

#include "Executor/Executor.h"

int main() {
	const char* input = " 0 ? 'a' | ! ? 'b' | 0 ? 'c' | 'd'";

	Blob blob = Compiler::Compile(input);

	Executor::Execute(blob);

	return 0;
}