#include "Compiler.h"

#include "./Lexer/Lexer.h"
#include "./Parser/Parser.h"
#include "./Expander/Expander.h"
#include "./Flattener/Flattener.h"
#include "./Encoder/Encoder.h"


namespace Compiler 
	Blob Compile(char* code) {
		std::vector<Token> tokens = Lex(code);

		std::vector<Node> node_flat = Parse(tokens);

		Node* node_tree = Expand(node_flat);

		EvalLink* eval_chain = Flatten(node_tree);

		Blob blob = Encode(eval_chain);
		
		return blob;
	}
}