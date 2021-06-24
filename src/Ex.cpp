#include <iostream>

#include "Core.h"
#include "Compiler/Compiler.h"

int main() {
	const char* input = "3 + 3";

	Blob blob = Compiler::Compile(input);

	return 0;
}