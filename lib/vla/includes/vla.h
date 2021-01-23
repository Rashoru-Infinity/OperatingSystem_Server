#ifndef VLA_H
#define VLA_H
#include "libtype.h"
#include <stdlib.h>
#include <stdbool.h>

typedef	struct	s_array {
	void		**contents;
	size_t		size;
	size_t		real_size;
}				t_array;

t_status	array_init(t_array *original, void (*func)(t_array *), size_t init_size);
t_status	array_extend(t_array *original);
void		array_elements_clear(t_array *arr, bool freeable);
void		array_clear(t_array *arr, bool elemfreeable, bool freeable);

#endif
