#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "utils/libft/libft.h"

// extern char **environ;

// typedef enum e_type
// {
// 	PIPE,
// 	END,
// 	WRITE,
// 	READ,
// 	APPEND
// }			 t_type;

// typedef struct s_file
// {
// 	char *filename;
// 	t_type type;
// }				t_file;

// typedef struct s_cmd
// {
// 	t_list *args;
// 	t_list *files;
// 	t_type type;
// }				t_cmd;

// t_list *cmds;

// void	ft_free(t_cmd *cmd)
// {
// 	while (cmd->args != NULL)
// 	{
// 		free(cmd->args->content);
// 		free(cmd->args);
// 		cmd->args = cmd->args->next;
// 	}
// }

int		main(int argc, char **argv, char **env)
{
	char	**tmp;
	int		i;

	return (0);
}

// int main ( int argc, char *argv[] )
// {
// 	int i, pid, ran;

// 	for(i = 0; i < atoi(argv[1]); i++) {
// 		pid = fork();
// 		// srand(time(NULL));
// 		// ran = (rand() % 10) + 1 ;

// 		if (pid < 0) {
// 			printf("Error");
// 			exit(1);
// 		} else if (pid == 0) {
// 			printf("Child (%d): %d\n", i + 1, getpid());
// 			printf("Sleep for = %d\n", ran);
// 			sleep(ran);
// 			// exit(ran);
// 		}
// 	}

// 	for(i = 0; i < atoi(argv[1]); i++) {
// 		int status = 0;
// 		pid_t childpid = wait(&status);
// 		printf("Parent knows child %d is finished. \n", (int)childpid);
// 	}
// }