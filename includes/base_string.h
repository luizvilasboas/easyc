#ifndef BASE_STRING_H_
#define BASE_STRING_H_

#include <stddef.h>

typedef struct {
    char *data;
    size_t size;
    size_t capacity;
} string;

string *string_create(const char *initial);
void string_destroy(string *str);
size_t string_length(const string *str);
size_t string_capacity(const string *str);
void string_concat(string *str, const char *suffix);
int string_compare(const string *str_1, const string *str_2);
void string_clear(string *str);
char *string_to_c(const string *str);
void string_reserve(string *str, size_t new_capacity);
void string_set(string *str, const char *new_value);
int string_contains(const string *str, const char *substring);
string **string_split(const string *str, const char *delimiter, size_t *num_tokens);
void string_replace(string *str, const char *old_substring, const char *new_substring);

#endif // BASE_STRING_H_
