/**
 * @file sstr.h
 * @brief simple string implement
 */

#ifndef SSTR_H_
#define SSTR_H_

#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief string type
 */
typedef void* sstr_t;

/**
 * @brief Create an empty sstr_t.
 *
 * @return sstr_t
 */
sstr_t sstr_new();

/**
 * @brief delete a sstr_t.
 *
 * @param s sstr_t instance to delete.
 */
void sstr_free(sstr_t s);

/**
 * @brief Create a sstr_t from \a data with \a length bytes.
 *
 * @param data data to copy to the result sstr_t.
 * @param length length of \a data.
 * @return sstr_t containing data copied from \a data.
 */
sstr_t sstr_of(const void* data, size_t length);

/**
 * @brief Create a sstr_t from C-style (NULL-terminated) string \a str.
 *
 * @param cstr C-style string to copy to the result sstr_t.
 * @return sstr_t containing \a data copied from cstr.
 */
sstr_t sstr(const char* cstr);

/**
 * @brief Return C-style string representation of \a s.
 *
 * @param s sstr_t instance to convert to C-style string.
 * @return char* C-style string representation of \a s.
 * @note The returned string is reused by \a s, do not free it.
 */
char* sstr_cstr(sstr_t s);

/**
 * @brief Return length of \a s.
 *
 * @param s sstr_t instance to get length of.
 * @return size_t length of \a s.
 */
size_t sstr_length(sstr_t s);

/**
 * @brief Compare \a a and \a b
 *        return 0 if equal, <0 if \a a < \a b, >0 if \a a > \a b.
 *
 * @param a sstr_t to be compared.
 * @param b sstr_t to be compared to.
 * @return int the compare result.
 * @note This function is case sensitive.
 */
int sstr_compare(sstr_t a, sstr_t b);

/**
 * @brief compare sstr_t \a a and \a c-style string b
 *
 * @return int
 */
int sstr_compare_c(sstr_t a, const char* b);

/**
 * @brief Append \a length byte of '\0' to \a s.
 *
 * @param s destination sstr_t.
 * @param length length of '\0' to append.
 */
void sstr_append_zero(sstr_t s, size_t length);

/**
 * @brief Append \a length byte of \a data to \a s.
 *
 * @param s destination sstr_t.
 * @param data data to append.
 * @param length length of \a data.
 */
void sstr_append_of(sstr_t s, const void* data, size_t length);

/**
 * @brief Append contents of \a src to \a dst.
 *
 * @param dst destination sstr_t.
 * @param src source sstr_t.
 */
void sstr_append(sstr_t dst, sstr_t src);

/**
 * @brief Duplicate \a s and return
 *
 * @param s sstr_t to duplicate.
 * @return sstr_t  duplicate of \a s.
 */
sstr_t sstr_dup(sstr_t s);

/**
 * @brief Get substring of \a s starting at \a index with \a length bytes.
 *
 * @param s sstr_t instance to get substring of.
 * @param index index of the first byte of the substring.
 * @param len number of bytes of the substring.
 * @return sstr_t substring of \a s.
 */
sstr_t sstr_substr(sstr_t s, size_t index, size_t len);

/**
 * @brief Printf implement.
 *
 * supported formats:
 *
 *   - %[0][width]T              time_t
 *   - %[0][width][u][x|X]z      ssize_t/size_t
 *   - %[0][width][u][x|X]d      int/u_int
 *   - %[0][width][u][x|X]l      long
 *   - %[0][width][u][x|X]D      int32_t/uint32_t
 *   - %[0][width][u][x|X]L      int64_t/uint64_t
 *   - %[0][width][.width]f      double, max valid number fits to %18.15f
 *   - %p                        void *
 *   - %S                        sstr_t
 *   - %s                        null-terminated string
 *   - %*s                       length and string
 *   - %Z                        '\0'
 *   - %N                        '\n'
 *   - %c                        char
 *   - %%                        %
 *
 *  reserved:
 *   - %C                        wchar
 *
 *  if %u/%x/%X, tailing d can be ignore
 */
sstr_t sstr_vslprintf(const char* fmt, va_list args);
sstr_t sstr_printf(size_t buf_size, const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* SSTR_H_  */
