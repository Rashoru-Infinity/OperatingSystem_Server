#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sha256.h"

char	*atoSHA256(const char *s)
{
	const int		len = 32;
	char			*value;
	unsigned char	*buf;
	SHA256_CTX		c;

	if (!(value = calloc(len + 1, sizeof(unsigned char))))
		return (NULL);
	if (!(buf = calloc(len + 1, sizeof(unsigned char))))
	{
		free(value);
		return (NULL);
	}
	SHA256_Init(&c);
	SHA256_Update(&c, s, strlen(s));
	SHA256_Final(buf, &c);
	for (int i = 0;i < len && buf[i];++i)
		sprintf(value + i, "%x", buf[i]);
	value[strlen(value)] = '\0';
	free(buf);
	return (value);
}
