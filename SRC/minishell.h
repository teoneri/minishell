/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:15:38 by mneri             #+#    #+#             */
/*   Updated: 2023/06/08 15:29:58 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../ft_printf/ft_printf.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <signal.h>
#include <fcntl.h>
/*!
 * @brief global variable used to update the error status
 * when signals are detected
 */
extern int g_status;

/*!
 * @brief cmd is the linked list containing a t_store node with all the commands
 * divided by pipes
 * envp is the array containing the values for the shell env
 */
typedef struct	s_carry
{
	t_list	*cmd;
	char **str;
	char	**envp;
	pid_t	pid;
}		t_carry;

/*!
 * @brief whole_cmd is used as argv containing the cmd name and its params
 * whole_path its the first available path for the executable (argv[0])
 */
typedef struct	s_store
{
	char	**whole_cmd;
	char	*whole_path;
	char	*here_doc;
	int	infile;
	int	outfile;
}		t_store;

enum	error
{
	DUPERROR = 1,
	FORKERROR = 2,
	CMDNOTFOUND = 3,
	PIPERROR = 4,
	DIRNOTFOUND = 5,
	FDERROR = 6
} ;

char	**ft_pipe_split(char *s, char c);
char	*ft_strchr2(char *s, int c, int k);
char	*ft_word_create(char *s, int start, char c);
char	**ft_cmdtrim(char *s, char c);
char **ft_expander(char **str, t_carry *prompt);
char **ft_cmdsubsplit(char **s);
t_list *ft_fillnode(char **splt, t_list *lst, t_carry *prompt);
int	ft_exec(t_list *cmd, t_carry *prompt, char ***str);
void	ft_export(t_store *stor, t_carry *prompt);
int	ft_findenv(char*usrvar, t_carry *prompt);
void	ft_unset(t_store *stor, t_carry *prompt);
void	ft_cd(t_store *stor, t_carry *prompt);
int		ft_handlehere_doc(t_store *stor);
void	ft_exit(t_carry *prompt, char **str);
void	ft_freecontent(void *content);
void	signal_handler(int sig);
void	ft_error(int error_typ, int err);
void	ft_echo(void);

