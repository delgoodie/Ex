#include "EvalLink.h"

#include <sstream>
#include "../../Operator/Operator.h"


namespace Executor {
    bool EvalLink::TypeFlag() {
        return flags & 0x80;
    }
    
    bool EvalLink::SideFlag() { 
        return flags & 0x40; 
    }
    
    bool EvalLink::LHSFlag() {
        return flags & 0x20; 
    }
    
    bool EvalLink::RHSFlag() {
        return flags & 0x10;
    }
    
    bool EvalLink::NullFlag() {
        return flags & 0x08; 
    }
    
    std::string EvalLink::ToString() const {
        std::stringstream ss;
        EvalLink* el = const_cast<EvalLink*>(this);
        while (el) {
            if (el->TypeFlag()) ss << Operator::STR[el->op.index];
            else ss << el->expr.ToString();
            ss << ' ';
            el = el->next;
        }
        return ss.str();
    }
}