#ifndef HASH_H
#define HASH_H
#include "vla.h"

typedef struct	s_hash {
	t_array	vla;
	size_t	(*hash_func)(void *, size_t max_size);
	int		(*is_same)(void *, void *);
}				t_hash;

t_status	hash_init(t_hash *original, size_t init_size, void (*pre_init_func)(t_array *),
			size_t (*hash_func)(void *, size_t max_size), int (*is_same)(void *, void *));
t_status	hash_add(t_hash *table, void *content);
t_status	hash_remove(t_hash *table, void *content, bool freeable);
void		hash_elements_clear(t_hash *table, bool freeable);
void		hash_clear(t_hash *table, bool elemfreeable, bool freeable);
int			hash_contains(t_hash table, void *content);
size_t		hash_size(t_hash table);

#endif
