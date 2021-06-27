#include <iostream>

#include "Core.h"
#include "Compiler/Compiler.h"

#include "Executor/Executor.h"

int main() {
	const char* input = "  { 3 + 4 } == 5  ";

	Blob blob = Compiler::Compile(input);

	Executor::Execute(blob);

	return 0;
}