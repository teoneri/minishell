#include "minishell.h"

char *ft_expjoin(char *var, char *envar, char *usrvar)
{
	char *str;
	int i;
	int size;
	int j;

	size = ft_strlen(envar) - (ft_strlen(var));
	str = malloc(sizeof(char) * size + 1);
	i = 0;
	j = 0;
	while(i < size)
	{
		if(var[j] == '$')
		{
			j += ft_strlen(usrvar) + 1;
		}
		str[i] = envar[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return(str);
}



int	ft_findenv(char*usrvar, t_carry *prompt)
{
	int i;

	i = 0;
	while(prompt->envp[i])
	{
		if(!ft_strncmp(prompt->envp[i], usrvar, ft_findchar(prompt->envp[i], '=')))
			return i;
		i++;
	}
	return -1;
}

char *ft_expandvar(char *var, t_carry *prompt)
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
			i++;
		start = i + 1;
		i++;
	}
    while(var[i] != '\0')
	{
		if(var[i] == ' ' || var[i] == '\''
		|| var[i] == '\"')
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
	if((i = ft_findenv(usrvar, prompt))!= 0)
    {
		envar = ft_strdup(prompt->envp[i]);
		return(ft_expjoin(var, envar, usrvar));
	}
	else
		return NULL;
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

char **ft_expander(char **str, t_carry *prompt)
{
	int i;

	i = 0;
    while(str[i] != NULL)
    {
        if(ft_strchr(str[i], '$'))
            str[i] = ft_expandvar(str[i], prompt);
		else if(ft_strchr(str[i], '~'))
			str[i] = ft_getpath(str[i]);
        i++;
    }
    return str;
}