#pragma once

#include <string.h>

namespace Evaluator {
    struct StringLink
    {
        StringLink* prev;
        char string[5];
        StringLink* next;

        StringLink(char s[5]) : prev(nullptr), next(nullptr) { memcpy(string, s, 5); }
        StringLink(StringLink* p, char s[5]) : prev(p), next(nullptr) { memcpy(string, s, 5); }
        StringLink(StringLink* p, char s[5], StringLink* n) : prev(p), next(n) { memcpy(string, s, 5); }
    };
}