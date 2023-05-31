
#include "libft.h"

int	ft_findchar(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return i;
		i++;
	}
	return (-1);
}