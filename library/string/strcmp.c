#include <string.h>

// compares two strings lexicographically
int strcmp(const char *str1, const char *str2)
{
	while (*str1 == *str2++) {
		if (*str1++ == 0) return 0;
	}
	
	return *(const char *)str1 - *(const char *)(str2 - 1);
} 
