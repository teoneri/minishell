#include "minishell.h"

char *ft_expandvar(char *var)
{
    int i;
    char *usrvar;
    char *envar;
    int k;
	int start;

    k = 0;
    i = 0;
	start = 0;
	if(var[i] == '$')
	{
		i++;
		start = i;
	}
	else
	{
		while(var[i] != '$')
		{
			i++;
		}
		start = i + 1;
		i++;
	}
    while(var[i] != '\0')
	{
		if(var[i] == ' ')
			break;
		i++;
        k++;
	}
    usrvar = ft_calloc(sizeof(char), k + 1);
	i = 0;
	while(k > 0)
	{
		usrvar[i++] = var[start++]; 
		k--;
	}
	usrvar[i] = '\0';
    envar = getenv(usrvar);
	return(envar);
}

char	*ft_getpath(char *tilde)
{
	int i;
	char *path;
	char *tmp;
	int start;
	int k;

	k = 0;
	path = getenv("HOME");
	if(tilde[0] != '~')
		return(tilde);
	i = 1;
	start = i;
	while(tilde[i] != ' ' && tilde[i] != '\0')
	{
		i++;
		k++;
	}
	i=0;
	tmp = ft_calloc(sizeof(char), k + 1);
	while(k > 0)
	{
		tmp[i++] = tilde[start++];
		k--;
	}
	path = ft_strjoin(path, tmp);
	return path;
}

char **ft_expander(char **prompt)
{
	int i;

	i = 0;
    while(prompt[i] != NULL)
    {
        if(ft_strchr(prompt[i], '$'))
            prompt[i] = ft_expandvar(prompt[i]);
		else if(ft_strchr(prompt[i], '~'))
			prompt[i] = ft_getpath(prompt[i]);
        i++;
    }
    return prompt;
}