#include <ctype.h>

int	is_safestr(const char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (!isascii(*s))
			return (0);
		if (!isgraph(*s))
			return (0);
		if ('!' <= *s && *s <= ',')
			return (0);
		if (*s == '.' || *s == '/')
			return (0);
		if (':' <= *s && *s <= '@')
			return (0);
		if ('[' <= *s && *s <= '^')
			return (0);
		if (*s == '`')
			return (0);
		if (*s > 'z')
			return (0);
		++s;
	}
	return (1);
}
