#pragma once

#include "../Core.h"

#include "Operations/Operations.h"

namespace Operator
{
	const char STR[NUM_OPS][4] = {
		"!",  // false
		".",  // access (lhs.rhs)   - "access"
		".",  // access (.rhs)      - "relative"
		".",  // access (.)         - "this"
		"^",  // eval with parameter
		"^",  // eval
		"#",  // sizeof
		"-",  // negate, delete
		"!",  // not
		"**", // exponent
		"%",  // modulus
		"*",  // multiply
		"/",  // divide
		"+",  // add (literal)
		"-",  // add (literal)
		"<",  // less than
		">",  // greater than
		"<=", // less than or equal to
		">=", // greater than or equal to
		"==", // equal to
		"!=", // not equal to
		"&&", // and
		"||", // or
		"?",  // if
		"|",  // else
		"=",  // assign
		"->", // return
		",",  // separate (lhs, rhs)
		",",  // separate (lhs,)
		";"   // jump
		":",  // catch
	};

	const int PREC[NUM_OPS] = {
		1,  // !      
		2,  // .
		2,  // .
		2,  // .
		3,  // ^
		3,  // ^
		4,  // #
		4,  // -
		5,  // !
		6,  // **
		6,  // %
		7,  // *
		7,  // /
		8,  // +
		8,  // -
		9,  // <
		9,  // >
		9,  // <=
		9,  // >=
		9,  // ==
		9,  // !=
		10, // &&
		11, // ||
		12, // ?
		13, // |
		14, // =
		15, // ->
		20, // ,
		20, // ,
		-1, // ;
		-1	// :s
	};

	const bool LHS[NUM_OPS] = {
		false, // !
		true,  // .
		false, // .
		false, // .
		true,  // ^
		false, // ^
		false, // #
		false, // -
		false, // !
		true,  // **
		true,  // %
		true,  // *
		true,  // /
		true,  // +
		true,  // -
		true,  // <
		true,  // >
		true,  // <=
		true,  // >=
		true,  // ==
		true,  // !=
		true,  // &&
		true,  // ||
		true,  // ?
		true,  // |
		true,  // =
		false, // ->
		true,  // ,
		true,  // ,
		false, // ;
		false  // :
	};

	const bool RHS[NUM_OPS] = {
		false, // !
		true,  // .
		true,  // .
		false, // .
		true,  // ^
		true,  // ^
		true,  // #
		true,  // -
		true,  // !
		true,  // **
		true,  // %
		true,  // *
		true,  // /
		true,  // +
		true,  // -
		true,  // <
		true,  // >
		true,  // <=
		true,  // >=
		true,  // ==
		true,  // !=
		true,  // &&
		true,  // ||
		true,  // ?
		true,  // |
		true,  // =
		true,  // ->
		true,  // ,
		false, // ,
		false, // ;
		false  // :
	};

	const int POS[NUM_OPS] = {
		1, // !
		1, // .
		1, // .
		1, // .
		1, // ^
		1, // ^
		1, // #
		1, // -
		1, // !
		1, // **
		1, // %
		1, // *
		1, // /
		1, // +
		1, // -
		1, // <
		1, // >
		1, // <=
		1, // >=
		1, // ==
		1, // !=
		1, // &&
		1, // ||
		0, // ?
		0, // |
		1, // =
		1, // ->
		1, // ,
		1, // ,
		1, // ;
		1  // :
	};
}