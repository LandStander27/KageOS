#include "bool.h"

int str_len(char *str) {
	int i = 0;
	while (str[i] != '\0') {
		i++;
	}
	return i;
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