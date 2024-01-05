#ifndef STRING_H
#define STRING_H

#include "bool.h"

void int_to_string(int num, char *str);
void repeat(char *str, char pattern, int times);
int str_len(char *str);
void reverse(char *str);
bool starts_with(char *str, char *prefix);
void strip_prefix(char *str, int prefix_len, char *stripped);

#endif