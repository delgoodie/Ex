#include "Compiler.h"

#include "./CompilerCore.h"

#include "./Lexer/Lexer.h"
#include "./Parser/Parser.h"
#include "./Expander/Expander.h"
#include "./Flattener/Flattener.h"
#include "./Encoder/Encoder.h"

namespace Compiler {
	Blob Compile(const char* code) {
		std::vector<Token_Comp> tokens = Lex(code);

		DEBUG_LOG(Debug::PrintTokens(tokens));

		std::vector<Node_Comp> node_flat = Parse(tokens);

		DEBUG_LOG(Debug::PrintNodeFlat(node_flat));

		Node_Comp* node_tree = Expand(node_flat);

		DEBUG_LOG(Debug::PrintNodeTree(node_tree));

		EvalLink_Comp* eval_chain = Flatten(node_tree);

		DEBUG_LOG(Debug::PrintLinkChain(eval_chain));

		Blob blob = Encode(eval_chain);

		DEBUG_LOG(Debug::PrintRawBlob(blob));
		
		return blob;
	}
}