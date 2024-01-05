#include "bool.h"
#include "screen.h"

int str_len(char *str) {
	int i = 0;
	while (str[i] != '\0') {
		i++;
	}
	return i;
}

bool starts_with(char *str, char *prefix) {
	int len = str_len(prefix);
	for (int i = 0; i < len; i++) {
		if (str[i] != prefix[i]) {
			return false;
		}
	}
	
	return true;
}

void strip_prefix(char *str, int prefix_len, char *stripped) {
	for (int i = prefix_len; i < str_len(str)-prefix_len; i++) {
		stripped[i-prefix_len] = str[i];
	}
}

void reverse(char *str) {

	int len = str_len(str);

	int start = 0;
	int end = len - 1;
	while (start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		end--;
		start++;
	}

	return;

}

void int_to_string(int num, char *str) {

	int i = 0;
	bool negative = false;
	if (num == 0) {
		str[0] = '0';
		str[1] = '\0';
		return;
	}

	if (num < 0) {
		negative = true;
		num = -num;
	}

	while (num != 0) {
		int remainder = num % 10;
		str[i] = remainder + '0';
		i++;
		num /= 10;
	}

	if (negative) {
		str[i] = '-';
		i++;
	}
	str[i] = '\0';

	reverse(str);

	return;

}

void repeat(char *str, char pattern, int times) {
	for (int i = 0; i < times; i++) {
		str[i] = pattern;
	}
	str[str_len(str)] = '\0';
}
