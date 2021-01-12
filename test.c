#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "utils/libft/libft.h"

extern char **environ;

typedef enum e_type
{
	PIPE,
	END,
	WRITE,
	READ,
	APPEND
}			 t_type;

typedef struct s_file
{
	char *filename;
	t_type type;
}				t_file;

typedef struct s_cmd
{
	t_list *args;
	t_list *files;
	t_type type;
}				t_cmd;


int		main(void)
{
	pid_t pid;
	int status;
	t_cmd *cmd;

	if (!(pid = fork()))
	{
		// in case of file
			int fd = open("test.c", O_CREAT | O_RDWR | O_APPEND, 0666);
			dup2(fd, 0);
		// end
		
		char *test = "echo -n hello";
		char *args[] = {
			"main.c",
			NULL
		};
		execve(test, args, environ);
		exit(0);
	}
	else
	{
		
		waitpid(pid, &status, 0);
	}
	
	return (0);
}

// | ; > < >> \t space
// " ' $