#include <string.h>

size_t strlen(string str)
{
	size_t length = 0;
	for(; str[length] != 0; length++);
	
	return length;
}
