
#include "libft.h"

void	ft_freematrix(char **str)
{
	int	i;

	i = 0;
	while(str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}