#ifndef SERVER_H
#define SERVER_H
#include "read_file.h"
#include "sha256.h"
#include "strutils.h"
#include "hash_set.h"
#include "libtype.h"

t_status	admit(const char *home, const char *hash);
char		*gen_repository(const char *home, const char *name);
size_t		hash_func(void *content, size_t max_size);
int			is_same(void *content1, void *content2);

#endif
