

#include "libft.h"                                                                                                                                      

char **ft_trimmatrix(char **mx, int pos)
{
    char **str;
    int i;
    int j;
    int len;

    j = 0;
    i = 0;
    len = ft_matrixlen(mx);
    str = malloc(sizeof(char *) * len);
    if (str == NULL)
        return NULL;
    while (mx[i])
    {
        if (i == pos)
            i++;
        str[j] = ft_strdup(mx[i]);
        i++;
        j++;
    }
    str[j] = NULL;
    return str;
}
