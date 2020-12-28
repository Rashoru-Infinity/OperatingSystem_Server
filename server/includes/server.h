#ifndef SERVER_H
#define SERVER_H
#include "read_file.h"
#include "sha256.h"

int		identify(const char *hash);
char	*gen_repository(const char *name);

#endif
