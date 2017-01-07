#include <string.h>

size_t length(string str)
{
	size_t len = 0;
	for(; str[len] != 0; len++);
	
	return len;
}
