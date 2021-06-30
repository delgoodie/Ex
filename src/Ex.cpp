#include <iostream>
#include <regex>
#include <fstream>

#include "Core.h"
#include "Compiler/Compiler.h"

#include "Executor/Executor.h"

int main(int argc, char* argv[]) {
	// Argument provided
	if (argc > 1) {
		char* code_buffer = nullptr;

		if (std::regex_match(argv[1], std::regex("[\\\\\\w :.]+\\.ex"))) {
			std::printf("Evaluating file: \"%s\"\n", argv[1]);

			std::ifstream code_file(argv[1], std::ios::binary | std::ios::ate);

			if (code_file.is_open()) {

				std::streamsize size = code_file.tellg();
				code_file.seekg(0, std::ios::beg);
				std::vector<char> code_char_vec(size);
				if (code_file.read(code_char_vec.data(), size))
				{
					code_buffer = new char[code_char_vec.size() + 1];
					for (int i = 0; i < code_char_vec.size(); i++) code_buffer[i] = code_char_vec[i];
					code_buffer[code_char_vec.size()] = '\0';
					std::printf("File: \"%s\"\n", code_buffer);
				}
				else {
					std::printf("Vector file read failed\n");
					return -1;
				}
			}
			else {
				std::printf("Invalid File\n");
				return -1;
			}
		}
		else {
			std::printf("Evaluating argument as code\n");
			code_buffer = argv[1];
		}


		Blob blob = Compiler::Compile(code_buffer);

		Executor::Execute(blob);

		return 0;
	}
	else {
		std::printf("No argument provided\n");
		return -1;
	}
}