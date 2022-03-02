#include <stdio.h>

#include "sstr.h"

int main() {
    sstr_t stotal = sstr_new();
    sstr_t s1 = sstr("hello");
    sstr_t s2 = sstr("world");
    sstr_append(stotal, s1);
    sstr_append_of(stotal, " ", 1);
    sstr_append(stotal, s2);
    sstr_free(s1);
    sstr_free(s2);

    sstr_t result = sstr_printf("stotal=%S, c-str=%s, int=%d, long=0x%ux", stotal,
                                "this is c str", 123, (unsigned long)0x456);

    puts(sstr_cstr(result));

    sstr_free(result);
    sstr_free(stotal);
    return 0;
}
