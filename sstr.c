#include "sstr.h"

#include <malloc.h>
#include <stdint.h>
#include <string.h>

#define SHORT_STR_CAPACITY 17

struct sstr_s {
    size_t length;
    union {
        char short_str[SHORT_STR_CAPACITY + 1];
        struct {
            char* long_str;
            size_t long_str_cap;
        };
    };
};
#define STR struct sstr_s

#define STR_SHORT_P(s) (((STR*)s)->length <= SHORT_STR_CAPACITY)
#define STR_PTR(s) (STR_SHORT_P(s) ? ((STR*)s)->short_str : ((STR*)s)->long_str)

sstr_t sstr_new() {
    STR* s = (STR*)malloc(sizeof(STR));
    memset(s, 0, sizeof(STR));
    return s;
}

void sstr_free(sstr_t s) {
    STR* ss = (STR*)s;
    if (STR_SHORT_P(ss) && ss->long_str) {
        free(ss->long_str);
    }
    free(s);
}

sstr_t sstr_of(const void* data, size_t length) {
    STR* s = (STR*)sstr_new();
    if (length <= SHORT_STR_CAPACITY) {
        memcpy(s->short_str, data, length);
    } else {
        s->long_str = (char*)realloc((void*)data, length);
        s->long_str_cap = length;
    }
    s->length = length;
    s->short_str[s->length] = '\0';
    return s;
}

sstr_t sstr(const char* cstr) { return sstr_of(cstr, strlen(cstr)); }

char* sstr_cstr(sstr_t s) { return STR_PTR(s); }

size_t sstr_length(sstr_t s) { return ((STR*)s)->length; }

int sstr_compare(sstr_t a, sstr_t b) {
    size_t alen = sstr_length(a), blen = sstr_length(b);
    size_t minlen = alen;
    if (minlen > blen) {
        minlen = blen;
    }

    int c = memcmp(STR_PTR(a), STR_PTR(b), minlen);
    if (c != 0) {
        return c;
    }
    return alen > blen;
}

void sstr_append_zero(sstr_t s, size_t length) {
    STR* ss = (STR*)s;
    if (STR_SHORT_P(s)) {
        if (SHORT_STR_CAPACITY - ss->length > length) {
            memset(ss->short_str + ss->length, 0, length);
            ss->length += length;
            return;
        }
    } else {
        if (ss->long_str_cap - ss->length > length) {
            memset(ss->long_str + ss->length, 0, length);
            ss->length += length;
            return;
        }
    }
    ss->long_str = (char*)realloc(STR_PTR(s), length + ss->length);
    memset(ss->long_str + ss->length, 0, length);
    ss->length += length;
}

void sstr_append_of(sstr_t s, const void* data, size_t length) {
    size_t oldlen = sstr_length(s);
    sstr_append_zero(s, length);
    memcpy(STR_PTR(s) + oldlen, data, length);
}

sstr_t sstr_substr(sstr_t s, size_t index, size_t len) {
    size_t minlen = len;
    size_t str_len = sstr_length(s);
    if (minlen > str_len) {
        minlen = str_len;
    }
    return sstr_of(STR_PTR(s) + index, minlen);
}
