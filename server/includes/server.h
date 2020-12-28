#ifndef SERVER_H
#define SERVER_H
#include "read_file.h"
#include "sha256.h"
#include "strutils.h"
#include "libtype.h"

t_status	admit(const char *hash);
char		*gen_repository(const char *name);

#endif
