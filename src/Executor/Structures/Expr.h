#pragma once

#include <string>

#include "../../Core.h"

#include "Object.h"

namespace Executor {

	struct EvalLink;
	struct StringLink;
	struct VarLink;
	struct ListLink;

	struct Expr
	{
		enum class Type : unsigned char
		{
			EX_NULL = 0,
			EX_BOOLEAN = 1,
			EX_NUMBER = 2,
			EX_STRING = 3,
			EX_VARIABLE = 4,
			EX_OBJECT = 5
		};
		Type type;
		union
		{
			ex_boolean_t boolean;
			ex_number_t number;
			struct
			{
				StringLink* head;
				size_t length;
			} string;
			struct
			{
				StringLink* name_head;
				VarLink* ptr;
			} variable;
			struct
			{
				ListLink* head;
				size_t length;
			} list;
			Object object;
		};

		Expr() : type(Type::EX_NULL) {}
		Expr(ex_boolean_t b) : type(Type::EX_BOOLEAN), boolean(b) {}
		Expr(ex_number_t n) : type(Type::EX_NUMBER), number(n) {}
		Expr(StringLink* s, size_t l) : type(Type::EX_STRING), string({ s, l }) {}
		Expr(StringLink* s, VarLink* v) : type(Type::EX_VARIABLE), variable({ s, v }) {}
		Expr(Object o) : type(Type::EX_OBJECT), object(o) {}
		Expr(std::nullptr_t null) : type(Type::EX_NULL) {}

		std::string ToString() const;
	};

}