#ifndef VLA_H
#define VLA_H
#include "libtype.h"
#include <stdlib.h>

typedef	struct	s_array {
	void		**content;
	size_t		size;
	size_t		real_size;
}				t_array;

t_status	array_init(t_array *original, void (*func)(t_array *), size_t init_size);
t_status	array_extend(t_array *original, void (*func)(t_array *));
void		array_element_clear(t_array *arr);
void		array_clear(t_array *arr);

#endif
