#include <iostream>
#include <regex>
#include <fstream>
#include <chrono>

#include "Core.h"
#include "Compiler/Compiler.h"

#include "Executor/Executor.h"

int main(int argc, char* argv[]) {
	// Argument provided
	if (argc > 1) {
		char* code_buffer = nullptr;

		if (std::regex_match(argv[1], std::regex("[\\\\\\w :.]+\\.ex"))) {
#ifdef _DEBUG
			std::printf("Evaluating file: \"%s\"\n", argv[1]);
#endif

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
#ifdef _DEBUG
					std::printf("\"\"\"\n%s\n\"\"\"\n", code_buffer);
#endif
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

		long long compileDuration, executionDuration;

		auto start = std::chrono::high_resolution_clock::now();

		Blob blob = Compiler::Compile(code_buffer);

		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		compileDuration = duration.count() / 1000;

		start = std::chrono::high_resolution_clock::now();

		Executor::Execute(blob);

		stop = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		executionDuration = duration.count() / 1000;

		std::printf("Compile Duration: %d ms\n", compileDuration);
		std::printf("Execution Duration: %d ms\n", executionDuration);


		return 0;
	}
	else {
		std::printf("No argument provided\n");
		return -1;
	}
}