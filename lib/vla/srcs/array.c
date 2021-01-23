#include "client.h"
#include <stdlib.h>

t_status array_init(t_array *arr, size_t init_size)
{
	if (!arr || !init_size)
		return (fail);
	if (!(arr->content = calloc(init_size, init_size)))
		return (fail);
	arr->size = init_size;
	return (success);
}

t_status array_extend(t_array *original, void (*func)(t_array *))
{
	void *new_array;

	if (!(original->size))
		return (fail);
	if (!(new_array = realloc(original->content, original->size)))
		return (fail);
	original->content = new_array;
	if (func)
		(*func)(original);
	return (success);
}
