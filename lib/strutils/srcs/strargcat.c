#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static size_t	*estimate_size(int argc, va_list ap)
{
	size_t	*size;
	char	*arg;

	if (!(size = calloc(1, sizeof(size_t))))
		return (NULL);
	while (argc-- > 0)
	{
		if (!(arg = va_arg(ap, char *)))
		{
			free(size);
			return (NULL);
		}
		*size += strlen(arg);
	}
	return (size);
}

char *strargcat(int argc, ...)
{
	va_list	ap;
	va_list	ap_est;
	size_t	*size;
	char	*arg;
	char	*str;

	va_start(ap, argc);
	va_copy(ap_est, ap);
	if (!(size = estimate_size(argc, ap_est)))
		return (NULL);
	if (!(str = malloc(sizeof(char) * (*size + 1))))
	{
		free(size);
		return (NULL);
	}
	*str = '\0';
	while (argc-- > 0)
	{
		arg = va_arg(ap, char *);
		strncat(str, arg, strlen(arg));
	}
	free(size);
	va_end(ap);
	va_end(ap_est);
	return (str);
}
