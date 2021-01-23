#include "vla.h"

t_status	array_init(t_array *arr, void (*func)(t_array *), size_t contents_num)
{
	if (!arr || !contents_num)
		return (fail);
	if (func)
		(*func)(arr);
	if (!(arr->contents = calloc(sizeof(void **) * contents_num, contents_num)))
		return (fail);
	arr->size = 0;
	arr->real_size = contents_num;
	return (success);
}

t_status	array_extend(t_array *original)
{
	void *new_array;

	if (!(original->real_size))
		return (fail);
	if (!(new_array = realloc(original->contents, 2 * original->real_size * sizeof(void **))))
		return (fail);
	original->contents = new_array;
	original->real_size *= 2;
	return (success);
}

void		array_elements_clear(t_array *arr, bool freeable)
{
	while (arr->contents && arr->size > 0)
	{
		if (freeable)
			free(arr->contents[arr->size - 1]);
		arr->contents[arr->size - 1] = NULL;
		--(arr->size);
	}
}

void		array_clear(t_array *arr, bool freeable, bool elemfreeable)
{
	array_elements_clear(arr, elemfreeable);
	if (freeable)
		free(arr->contents);
	arr->contents = NULL;
	arr->real_size = 0;
}
