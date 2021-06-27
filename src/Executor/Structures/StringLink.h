#pragma once

#include <string.h>
#include <sstream>
#include <string>

namespace Executor {
    struct StringLink
    {
        StringLink* prev;
        char string[5];
        StringLink* next;

        StringLink(char s[5]) : prev(nullptr), next(nullptr) { memcpy(string, s, 5); }
        StringLink(StringLink* p, char s[5]) : prev(p), next(nullptr) { memcpy(string, s, 5); }
        StringLink(StringLink* p, char s[5], StringLink* n) : prev(p), next(n) { memcpy(string, s, 5); }

        std::string ToString() const {
            std::stringstream ss;
            StringLink* sl = const_cast<StringLink*>(this);
            while (sl) {
                ss << sl->string;
                sl = sl->next;
            }
            return ss.str();
        }
    };
}