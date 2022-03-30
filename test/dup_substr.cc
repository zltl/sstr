#include <gtest/gtest.h>
#include <stdio.h>  /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <unistd.h>

#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "sstr.h"

std::string gen_random(const int len);

TEST(dup, simple) {
    for (int i = 0; i < 10000; ++i) {
        auto s = gen_random(i + 1);
        sstr_t ss = sstr(s.c_str());
        sstr_t ss2 = sstr_dup(ss);
        ASSERT_EQ(s, sstr_cstr(ss));
        ASSERT_EQ(sstr_compare(ss, ss2), 0);

        sstr_free(ss2);
        sstr_free(ss);
    }
}

TEST(substr, simple) {
    for (int i = 0; i < 10000; ++i) {
        auto s = gen_random(i + 1);
        sstr_t ss = sstr(s.c_str());
        sstr_t ss2 = sstr_substr(ss, rand() % sstr_length(ss), rand());
        ASSERT_LE(sstr_length(ss2), sstr_length(ss));

        sstr_clear(ss2);
        sstr_clear(ss);
        ASSERT_EQ(sstr_length(ss2), 0);
        ASSERT_EQ(sstr_length(ss), 0);

        sstr_free(ss2);
        sstr_free(ss);
    }
}
