#include "hash_set.h"
#include <stdbool.h>
#include <string.h>

static int		has_space(t_hash table)
{
	while (table.vla.real_size > 0)
	{
		if (!table.vla.contents[table.vla.real_size - 1])
			return (1);
		--table.vla.real_size;
	}
	return (0);
}

static t_status	get_space_index(t_hash table, void *content, size_t *val)
{
	size_t	hash_val;
	size_t	initial_val;

	hash_val = (*(table.hash_func))(content, table.vla.real_size);
	initial_val = hash_val;
	if (initial_val >= table.vla.real_size)
		return (fail);
	while (table.vla.contents[hash_val])
	{
		if ((*(table.is_same))(content, table.vla.contents[hash_val]))
			return (fail);
		++hash_val;
		hash_val %= table.vla.real_size;
		if (hash_val == initial_val)
			return (fail);
	}
	*val = hash_val;
	return (success);
}

static t_status	hash_ext(t_hash *table)
{
	void	**tmp;
	size_t	index;
	size_t	hash_val;
	size_t	pre_size;

	if (!(tmp = malloc(sizeof(void *) * table->vla.real_size)))
		return (fail);
	memcpy(tmp, table->vla.contents, sizeof(void *) * table->vla.real_size);
	index = table->vla.real_size;
	pre_size = table->vla.size;
	if (array_extend(&(table->vla)) == fail)
		return (fail);
	bzero(table->vla.contents, sizeof(void *) * table->vla.real_size);
	while (index > 0)
	{
		if (!tmp[--index])
			continue;
		if (get_space_index(*table, tmp[index], &hash_val) == fail)
		{
			table->vla.size = pre_size;
			free(table->vla.contents);
			table->vla.contents = tmp;
			return (fail);
		}
		table->vla.contents[hash_val] = tmp[index];
	}
	free(tmp);
	return (success);
}

static t_status	search_content(t_hash table, void *content, size_t *index)
{	
	size_t	hash_val;
	size_t	initial_val;

	hash_val = (*(table.hash_func))(content, table.vla.real_size);
	initial_val = hash_val;
	if (initial_val >= table.vla.real_size)
		return (fail);
	while (table.vla.contents[hash_val])
	{
		if ((*(table.is_same))(content, table.vla.contents[hash_val]))
		{
			if (index)
				*index = hash_val;
			return (success);
		}
		++hash_val;
		hash_val %= table.vla.real_size;
		if (hash_val == initial_val)
			return (fail);
	}
	return (fail);
}

t_status		hash_init(t_hash *original, size_t init_size, void (*pre_init_func)(t_array *),
				size_t (*hash_func)(void *, size_t), int (*is_same)(void *, void *))
{
	if (!original || !init_size)
		return (fail);
	if (array_init(&(original->vla), pre_init_func, init_size) == fail)
		return (fail);
	original->hash_func = hash_func;
	original->is_same = is_same;
	return (success);
}

t_status		hash_add(t_hash *table, void *content)
{
	size_t	hash_val;

	if (!table || !content || !table->hash_func)
		return (fail);
	if (search_content(*table, content, NULL) == success)
		return (success);
	if (!has_space(*table))
	{
		if (hash_ext(table) == fail)
			return (fail);
	}
	if (get_space_index(*table, content, &hash_val) == fail)
		return (fail);
	table->vla.contents[hash_val] = content;
	return (success);
}

t_status		hash_remove(t_hash *table, void *content, bool freeable)
{
	size_t	index;

	if (!table || !content || !(table->hash_func) || !(table->is_same))
		return (fail);
	if (search_content(*table, content, &index) == fail)
		return (fail);
	if (freeable)
		free(table->vla.contents[index]);
	table->vla.contents[index] = NULL;
	return (success);
}

void	hash_elements_clear(t_hash *table, bool freeable)
{
	array_elements_clear(&(table->vla), freeable);
}

void	hash_clear(t_hash *table, bool elemfreeable, bool freeable)
{
	array_clear(&(table->vla), elemfreeable, freeable);
}

int		hash_contains(t_hash table, void *content)
{
	if (!content || !(table.hash_func) || !(table.is_same))
		return (fail);
	return (search_content(table, content, NULL) == success);
}

size_t	hash_size(t_hash table)
{
	size_t	size;

	size = 0;
	while (--table.vla.real_size > 0)
	{
		if (table.vla.contents[table.vla.real_size])
			++size;
	}
	return (size);
}
