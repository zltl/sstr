#include <gtest/gtest.h>
#include <stdio.h>  /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <unistd.h>

#include <iomanip>
#include <iostream>
#include <random>

using std::cout;
using std::endl;
using std::setprecision;

#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "sstr.h"

std::string gen_random(const int len);

TEST(printf, int) {
    for (int i = 0; i < 10000; ++i) {
        sstr_t r = sstr_printf("thisis%dinteger", i);
        char tmp[1000];
        snprintf(tmp, sizeof(tmp), "thisis%dinteger", i);
        ASSERT_EQ(sstr_compare_c(r, tmp), 0);
        sstr_free(r);
    }
    for (int i = 0; i < 10000; ++i) {
        sstr_t r = sstr_printf("thisis%dinteger", -i);
        char tmp[1000];
        snprintf(tmp, sizeof(tmp), "thisis%dinteger", -i);
        ASSERT_EQ(sstr_compare_c(r, tmp), 0);
        sstr_free(r);
    }
}
TEST(printf, long) {
    for (long i = 0; i < 10000; ++i) {
        sstr_t r = sstr_printf("thisis%linteger", i);
        char tmp[1000];
        snprintf(tmp, sizeof(tmp), "thisis%ldinteger", i);
        ASSERT_EQ(sstr_compare_c(r, tmp), 0);
        sstr_free(r);
    }
    for (long i = 0; i < 10000; ++i) {
        sstr_t r = sstr_printf("thisis%linteger", -i);
        char tmp[1000];
        snprintf(tmp, sizeof(tmp), "thisis%ldinteger", -i);
        ASSERT_EQ(sstr_compare_c(r, tmp), 0);
        sstr_free(r);
    }
}
TEST(printf, float) {
    constexpr int kFloatMin = 0;
    constexpr int kFloatMax = 100;
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<> distr(kFloatMin, kFloatMax);

    for (long i = 0; i < 10000; ++i) {
        float f = (float)distr(eng);
        sstr_t r = sstr_printf("thisis%.10ffloat", f);
        char tmp[1000];
        snprintf(tmp, sizeof(tmp), "thisis%.10ffloat", f);
        printf("%.10f--%s\n", f, sstr_cstr(r));
        /* TODO: compare round
        ASSERT_EQ(sstr_compare_c(r, tmp), 0)
            << "f:" << f << " tmp:" << tmp << " r:" << sstr_cstr(r) << endl;
            */
        sstr_free(r);
    }
    for (long i = 0; i < 10000; ++i) {
        float f = -(float)distr(eng);
        sstr_t r = sstr_printf("thisis%.10ffloat", f);
        char tmp[1000];
        snprintf(tmp, sizeof(tmp), "thisis%.10ffloat", f);
        printf("%.10f--%s\n", f, sstr_cstr(r));
        /* TODO: compare round
        ASSERT_EQ(sstr_compare_c(r, tmp), 0)
            << "f:" << f << " tmp:" << tmp << " r:" << sstr_cstr(r) << endl;
            */
        sstr_free(r);
    }
}

TEST(printf, sstr) {
    for (long i = 0; i < 10000; ++i) {
        auto s = gen_random(i + 1);
        sstr_t ss = sstr(s.c_str());
        sstr_t r = sstr_printf("%S", ss);
        ASSERT_EQ(sstr_compare(ss, r), 0);
        sstr_free(r);
        sstr_free(ss);
    }
}
