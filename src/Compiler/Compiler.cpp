#include "Compiler.h"

#include "./CompilerCore.h"

#include "./Lexer/Lexer.h"
#include "./Parser/Parser.h"
#include "./Expander/Expander.h"
#include "./Flattener/Flattener.h"
#include "./Encoder/Encoder.h"


namespace Compiler {
	Blob Compile(const char* code) {
		std::vector<Token> tokens = Lex(code);

		Debug::PrintTokens(tokens);

		std::vector<Node> node_flat = Parse(tokens);

		Debug::PrintNodeFlat(node_flat);

		Node* node_tree = Expand(node_flat);

		Debug::PrintNodeTree(node_tree);

		EvalLink* eval_chain = Flatten(node_tree);

		Debug::PrintLinkChain(eval_chain);

		Blob blob = Encode(eval_chain);

		Debug::PrintRawBlob(blob);
		
		return blob;
	}
}