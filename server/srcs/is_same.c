#include <string.h>

int	is_same(void *content1, void *content2)
{
	return (!strcmp(content1, content2) ? 1 : 0);
}
