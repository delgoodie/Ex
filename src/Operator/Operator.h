#pragma once

#include "../Core.h"

#include "Operations/Operations.h"

namespace Operator
{
	const char STR[NUM_OPS][4] = {
		"$",  // param
		"!",  // false
		".",  // access (lhs.rhs)   - property/index of object/list
		".",  // access (lhs.)      - parent index
		".",  // access (.rhs)      - explicit local
		".",  // access (.)         - "this"
		"^",  // eval with parameter
		"^",  // eval
		"++", // increment
		"--", // decrement
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
		":",  // catch
		";",  // jump
		",",  // separate (lhs, rhs)
		","   // separate (lhs,)
	};

	const int PREC[NUM_OPS] = {
		1,  // $      
		1,  // !      
		2,  // .
		2,  // .
		2,  // .
		2,  // .
		3,  // ^
		3,  // ^
		4,  // ++
		4,  // --
		5,  // #
		5,  // -
		6,  // !
		7,  // **
		7,  // %
		8,  // *
		8,  // /
		9,  // +
		9,  // -
		10,  // <
		10,  // >
		10,  // <=
		10,  // >=
		10,  // ==
		10,  // !=
		11, // &&
		12, // ||
		13, // ?
		14, // |
		15, // =
		16, // ->
		17,	// :
		4, // ;
		18, // ,
		18  // ,
	};

	const bool LHS[NUM_OPS] = {
		false, // $
		false, // !
		true,  // .
		true,  // .
		false, // .
		false, // .
		true,  // ^
		false, // ^
		true,  // ++
		true,  // --
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
		false, // :
		true,  // ;
		true,  // ,
		true   // ,
	};

	const bool RHS[NUM_OPS] = {
		false, // $
		false, // !
		true,  // .
		false, // .
		true,  // .
		false, // .
		true,  // ^
		true,  // ^
		false, // ++
		false, // --
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
		true,  // :
		false, // ;
		true,  // ,
		false  // ,
	};

	const int POS[NUM_OPS] = {
		1, // $
		1, // !
		1, // .
		1, // .
		1, // .
		1, // .
		1, // ^
		1, // ^
		1, // ++
		1, // --
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
		0, // :
		1, // ;
		0, // ,
		0  // ,
	};
}