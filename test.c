# include "pipex.h"

int main(void)
{
	int	fd_1[2];
	int fd_2[2];
	if (access("./pruebas.txt", F_OK) == -1)
		perror("ERROR");
	char *const argv[] = {"cat", "pruebas.txt", "-e", NULL};
	int pid = fork();
	ft_printf("FT_PRINTF ERROR: %s\n", strerror(errno));
	int file = open("./pruebas.txt", O_RDONLY);
	pipe(fd_1);
	dup2(file, fd_1[1]);
	close(fd_1[0]);
	if (pid == 0)
	{
		pipe(fd_2);
		close(fd_2[1]);
		if(execve("/bin/cat", argv, NULL) == -1)
			perror("ERROR");
	}
	else
	{
		wait(NULL);
		ft_printf("%i\n", access("./pruebas.txt", F_OK));
	}
	// char *const argv[] = {"-la", NULL};
	// char *const argv2[] = {"", NULL};
	// execve("/bin/ls", argv, NULL);
	// execve("/bin/pwd", argv2, NULL);
	return (0);
}