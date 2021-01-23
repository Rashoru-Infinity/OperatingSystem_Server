#include "vla.h"

t_status	array_init(t_array *arr, void (*func)(t_array *), size_t contents_num)
{
	if (!arr || !contents_num)
		return (fail);
	if (func)
		(*func)(arr);
	if (!(arr->content = calloc(sizeof(void **) * contents_num, contents_num)))
		return (fail);
	arr->size = 0;
	arr->real_size = contents_num;
	return (success);
}

t_status	array_extend(t_array *original, void (*func)(t_array *))
{
	void *new_array;

	if (!(original->real_size))
		return (fail);
	if (!(new_array = realloc(original->content, 2 * original->real_size * sizeof(void **))))
		return (fail);
	original->content = new_array;
	original->real_size *= 2;
	if (func)
		(*func)(original);
	return (success);
}

void		array_element_clear(t_array *arr)
{
	while (arr->content && arr->size > 0)
	{
		free(arr->content[arr->size - 1]);
		arr->content[arr->size - 1] = NULL;
		--(arr->size);
	}
}

void		array_clear(t_array *arr)
{
	array_element_clear(arr);
	free(arr->content);
	arr->content = NULL;
	arr->real_size = 0;
}
