#include "EvalLink.h"

namespace Evaluator {
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
}