#include "Encoder.h"

#include <string>
#include <string.h>
#include <fstream>
#include <iostream>

#include "../CompilerCore.h"

namespace Compiler
{
	static size_t EvalChainSize(EvalLink_Comp* chain)
	{
		size_t size = 0;
		EvalLink_Comp* link = chain;
		while (link)
		{
			size += 1; // Flags
			if (link->type == EvalLink_Comp::Type::OP)
				size += sizeof(int) + sizeof(int); // op index & jump
			else
			{
				size += sizeof(unsigned char); // Expr Type
				switch (link->expr.type)
				{
				case Expr_Comp::Type::EX_BOOLEAN:
					size += sizeof(ex_boolean_t);
					break;
				case Expr_Comp::Type::EX_NUMBER:
					size += sizeof(ex_number_t);
					break;
				case Expr_Comp::Type::EX_STRING:
					size += link->expr.string.length() + 1;
					break;
				case Expr_Comp::Type::EX_VARIABLE:
					size += link->expr.variable.length() + 1;
					break;
				case Expr_Comp::Type::EX_OBJECT:
					size += sizeof(size_t) + EvalChainSize(link->expr.object);
					break;
				}
			}
			link = link->next;
		}
		// Null link for termination
		size += sizeof(unsigned char);
		return size;
	}

	static void StoreBlob(Blob blob, const std::string& filename)
	{
		std::ofstream(filename, std::ios::binary).write((const char*)blob.data, blob.size);
		delete blob.data;
	}

	Blob Encode(EvalLink_Comp* head) {
		size_t size = EvalChainSize(head);
		// Allocate blob on heap
		unsigned char* data = (unsigned char*)malloc(size);

		memset(data, 0, size);

		// Write each link onto heap sequentially
		int index = 0;
		EvalLink_Comp* link = head;
		while (link)
		{
			data[index] = link->Flags(); // * Write Link Flags (1 byte)
			index += sizeof(unsigned char);

			if (link->type == EvalLink_Comp::Type::OP)
			{
				memcpy(&data[index], &link->op.index, sizeof(int));
				index += sizeof(int);
				memcpy(&data[index], &link->op.jump, sizeof(int));
				index += sizeof(int);
			}
			else
			{
				data[index] = (unsigned char)link->expr.type; // * Write Expr Type (1 byte)
				index += sizeof(unsigned char);

				switch (link->expr.type)
				{
				case Expr_Comp::Type::EX_BOOLEAN:
					data[index] = (link->expr.boolean ? 0xFF : 0x00); // * Write boolean (1 byte)
					index += sizeof(unsigned char);
					break;
				case Expr_Comp::Type::EX_NUMBER:
					memcpy(&data[index], &link->expr.number, sizeof(ex_number_t)); // * Write number (8 bytes if ex_number_type == double)
					index += sizeof(ex_number_t);
					break;
				case Expr_Comp::Type::EX_STRING:
					memcpy(&data[index], link->expr.string.c_str(), link->expr.string.length() + 1); // Write char* (n bytes)
					index += link->expr.string.length() + 1;
					break;
				case Expr_Comp::Type::EX_VARIABLE:
					memcpy(&data[index], link->expr.variable.c_str(), link->expr.variable.length() + 1); // Write char* (n bytes)
					index += link->expr.variable.length() + 1;
					break;
				case Expr_Comp::Type::EX_OBJECT:
					Blob obj = Encode(link->expr.object);
					memcpy(&data[index], &obj.size, sizeof(size_t));
					index += sizeof(size_t);
					memcpy(&data[index], obj.data, obj.size); // * Write eval chain (n bytes)
					index += obj.size;
					delete obj.data;
					break;
				}
			}
			link = link->next;
		}

		// Add null termination link
		data[index] = 0x08;

		// Return in blob form
		return { data, size };
	}

	namespace Debug
	{
		void PrintRawBlob(Blob blob) {
			std::printf("Printing Raw Blob:");
			for (int i = 0; i < blob.size; i++) {
				if (!(i % 10)) std::printf(" ");
				if (!(i % 40)) std::printf("\n");
				std::printf("%X", (int)blob.data[i]);
			}
			std::printf("\n\n");
		}
	}
}