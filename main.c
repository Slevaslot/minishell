#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>

int main() {
	char buf[100];
	char *line;

	printf("%s : ", getenv("PWD"));
	while(1)
	{
		line = readline(buf);
		if (!strncmp(line, "exit", 5))
			break ;
		if (line != NULL) {
			printf("%s : ", getenv("PWD"));
		} else {
			printf("Error or end of file.\n");
		}

	}
	return 0;
}
