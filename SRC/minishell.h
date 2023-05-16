
#include "../ft_printf/ft_printf.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

char	**ft_pipe_split(char *s, char c);
char	*ft_word_create(char *s, int start, char c);
char	**ft_cmdtrim(char *s, char c);
char **ft_expander(char **prompt);
char **ft_cmdsubsplit(char **s);


