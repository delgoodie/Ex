#include "EvalLink.h"

namespace Compiler {
	EvalLink::~EvalLink() {
		delete next;
	}


    unsigned char EvalLink::Flags()
    {
        // TODO: use for unused bits?
        unsigned char flags = 0x00;
        flags |= (type == EvalLink::Type::OP ? 0x80 : 0x00);  // EvalLink Type Flag (0 = expr, 1 = op)
        flags |= (side == EvalLink::Side::LHS ? 0x40 : 0x00); // EvalLink Side Flag (0 = rhs, 1 = lhs)
        flags |= (lhs ? 0x20 : 0x00);                         // Consumes LHS Flag (0 = false, 1 = true)
        flags |= (rhs ? 0x10 : 0x00);                         // Consumes RHS Flag (0 = false, 1 = true)
        flags |= (false ? 0x08 : 0x00);                       // Null EvalLink Flag (only used for chain termination)
        flags |= (false ? 0x04 : 0x00);                       // Unused bit
        flags |= (false ? 0x02 : 0x00);                       // Unused bit
        flags |= (false ? 0x01 : 0x00);                       // Unused bit
        return flags;
    }

    EvalLink::Type EvalLink::TypeFromFlags(unsigned char flags) {
        return (flags & 0x80 ? Type::OP : Type::EXPR);
    }
    EvalLink::Side EvalLink::SideFromFlags(unsigned char flags) {
        return (flags & 0x40 ? Side::LHS : Side::RHS);
    }
    bool EvalLink::LhsFromFlags(unsigned char flags) 
    {
        return flags & 0x20;
    }
    bool EvalLink::RhsFromFlags(unsigned char flags) {
        return flags & 0x10;
    }
    bool EvalLink::NullFromFlags(unsigned char flags) {
        return flags & 0x08;
    }
}