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

TEST(create, compare) {
    for (int i = 0; i < 10000; ++i) {
        auto s = gen_random(i + 1);
        sstr_t ss = sstr(s.c_str());
        sstr_t ss2 = sstr_of(s.c_str(), s.size());
        ASSERT_EQ(s, sstr_cstr(ss));
        ASSERT_EQ(sstr_compare_c(ss, s.c_str()), 0);
        ASSERT_EQ(sstr_compare(ss2, ss), 0);
        ASSERT_EQ(sstr_length(ss), s.size());
        sstr_free(ss2);
        sstr_free(ss);
    }
}
