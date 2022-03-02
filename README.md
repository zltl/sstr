sstr
--- 

- [View sstr on GitHub](https://github.com/zltl/sstr)
- [Document](https://zltl.github.io/sstr/)

`sstr_t` are objects that represent sequences of characters.
The standard C style string is a sequence of characters terminated
by a null character, which is easy to cause buffer overflow. And it's
annoying to pass pointer and length of string to every whare.

The sequence of characters just like a string in C++, inside the sstr_t
struct, it also has a null character at the end, so that we can use
sstr_t as a C style string.

sstr_t contains a pointer to char sequence and its length, solves the
security problems of standard C string. With functions bundle with sstr_t,
you can easily manipulate the string just like standard C string, but in a
safer way:

```C
sstr_t stotal = sstr_new();
sstr_t s1 = sstr("hello");
sstr_t s2 = sstr("world");
sstr_append(stotal, s1);
sstr_append_of(stotal, " ", 1);
sstr_append(stotal, s2);
sstr_free(s1);
sstr_free(s2);

sstr_t result = sstr_printf("stotal=%S, c-str=%s, int=%d, long=%ld",
    stotal, stotal, 123, (long)456);

puts(sstr_cstr(result));
sstr_free(result);
sstr_free(stotal);
```
