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

TEST(append, zero) {
    sstr_t s = sstr_new();
    std::string cpp_str;
    long cnt = 0;
    for (int i = 0; i < 1000; ++i) {
        cnt += i + 1;
        sstr_append_zero(s, i + 1);
    }
    ASSERT_EQ(cnt, sstr_length(s));
    for (long i = 0; i < cnt; ++i) {
        ASSERT_EQ(0, sstr_cstr(s)[i]);
    }
    sstr_free(s);
}

TEST(append, random) {
    sstr_t s_apof = sstr_new();
    sstr_t s_apc = sstr_new();
    sstr_t s_ap = sstr_new();
    std::string cpp_str;
    long cnt = 0;
    for (int i = 0; i < 1000; ++i) {
        cnt += i + 1;
        auto rand_str = gen_random(i + 1);
        sstr_append_of(s_apof, rand_str.c_str(), rand_str.size());
        sstr_append_cstr(s_apc, rand_str.c_str());
        sstr_t tmp = sstr(rand_str.c_str());
        sstr_append(s_ap, tmp);
        sstr_free(tmp);
        cpp_str.insert(cpp_str.end(), rand_str.begin(), rand_str.end());
    }
    ASSERT_EQ(cnt, sstr_length(s_apof));
    ASSERT_EQ(cnt, sstr_length(s_apc));
    ASSERT_EQ(cnt, sstr_length(s_ap));
    for (long i = 0; i < cnt; ++i) {
        ASSERT_EQ(sstr_cstr(s_apof)[i], sstr_cstr(s_apc)[i]);
        ASSERT_EQ(sstr_cstr(s_apof)[i], sstr_cstr(s_ap)[i]);
        ASSERT_EQ(sstr_cstr(s_apc)[i], cpp_str[i]);
    }
    sstr_free(s_apof);
    sstr_free(s_apc);
    sstr_free(s_ap);
}
