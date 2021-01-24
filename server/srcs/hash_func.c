#include <string.h>

size_t	hash_func(void *content, size_t max_size)
{
	size_t			hash_val;
	size_t			index;
	unsigned char	*str;

	str = content;
	hash_val = 0;
	index = strlen(content);
	while (index-- > 0)
		hash_val += str[index];
	return (hash_val % max_size);
}
