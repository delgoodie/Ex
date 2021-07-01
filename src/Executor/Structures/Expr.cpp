#include "Expr.h"

#include "StringLink.h"
#include "EvalLink.h"

namespace Executor {
	std::string Expr::ToString() const {
		if (type == Type::EX_NULL) return "null";
		else if (type == Type::EX_BOOLEAN) return boolean ? "true" : "false";
		else if (type == Type::EX_NUMBER) {
			char buffer[50];
			std::snprintf(buffer, 50, "%g", number);
			return std::string(buffer);
		}
		else if (type == Type::EX_STRING) return "'" + string.head->ToString() + "'";
		else if (type == Type::EX_VARIABLE) return "@" + variable.name_head->ToString();
		else if (type == Type::EX_OBJECT) return "{ " + object.e_head->ToString() + "}";
		else return "no type";
	}

	std::string Expr::TypeToString(Type type) {
		switch (type) {
		case Type::EX_NULL:
			return "NULL";
		case Type::EX_BOOLEAN:
			return "BOOL";
		case Type::EX_NUMBER:
			return "NUM";
		case Type::EX_STRING:
			return "STR";
		case Type::EX_VARIABLE:
			return "VAR";
		case Type::EX_OBJECT:
			return "OBJ";
		}
	}

}