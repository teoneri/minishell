/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:08:53 by lfai              #+#    #+#             */
/*   Updated: 2023/06/12 13:53:43 by lfai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_var_supp(char *var, int *i, int *k)
{
	int	start;

	start = 0;
	if (var[*i] == '$')
	{
		*i += 1;
		start = *i;
	}
	else
	{
		while (var[*i] != '$')
			*i += 1;
		start = *i + 1;
		*i += 1;
	}
	while (var[*i] != '\0')
	{
		if (var[*i] == ' ' || var[*i] == '\'' \
		|| var[*i] == '\"')
			break ;
		*i += 1;
		*k += 1;
	}
	return (start);
}

char	*ft_expandvar(char *var, t_carry *prompt)
{
	int		i;
	char	*usrvar;
	char	*envar;
	int		k;
	int		start;

	i = 0;
	k = 0;
	start = exp_var_supp(var, &i, &k);
	usrvar = ft_calloc(sizeof(char), k + 1);
	i = 0;
	while (k > 0)
	{
		usrvar[i++] = var[start++];
		k--;
	}
	usrvar[i] = '\0';
	i = ft_findenv(usrvar, prompt);
	if (i >= 0)
	{
		envar = ft_strdup(prompt->envp[i]);
		return (ft_expjoin(var, envar, usrvar));
	}
	free(usrvar);
	return (var);
}

void	get_path_supp(char *tilde, char *tmp, char *path, int k)
{
	int	start;
	int	i;

	i = 0;
	start = i;
	while (k > 0)
	{
		tmp[i++] = tilde[start++];
		k--;
	}
	path = ft_strjoin(path, tmp);
	free(tmp);
	free(tilde);
}

char	*ft_getpath(char *tilde)
{
	int		i;
	char	*path;
	char	*tmp;
	int		k;

	k = 0;
	path = getenv("HOME");
	if (tilde[0] != '~')
		return (tilde);
	i = 1;
	while (tilde[i] != ' ' && tilde[i] != '\0')
	{
		i++;
		k++;
	}
	i = 0;
	tmp = ft_calloc(sizeof(char), k + 1);
	get_path_supp(tilde, tmp, path, k);
	return (path);
}

char	**ft_expander(char **str, t_carry *prompt)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_strchr(str[i], '$'))
			str[i] = ft_expandvar(str[i], prompt);
		else if (ft_strchr(str[i], '~'))
			str[i] = ft_getpath(str[i]);
		i++;
	}
	return (str);
}
