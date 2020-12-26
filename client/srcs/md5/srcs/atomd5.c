#include <openssl/md5.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "md5.h"

char	*atomd5(const char *s)
{
	const int		len = 32;
	char			*value;
	unsigned char	*buf;
	MD5_CTX			c;

	if (!(value = calloc(len + 1, sizeof(unsigned char))))
		return (NULL);
	if (!(buf = calloc(len + 1, sizeof(unsigned char))))
	{
		free(value);
		return (NULL);
	}
	MD5_Init(&c);
	MD5_Update(&c, s, strlen(s));
	MD5_Final(buf, &c);
	for (int i = 0;i < len && buf[i];++i)
		sprintf(value + i, "%x", buf[i]);
	value[strlen(value)] = '\0';
	free(buf);
	return (value);
}
