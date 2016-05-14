#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "header.h"
#include <dirent.h>
#include "libshell/libshell.h"

#define BUFFER_SIZE 100

/*
 * Takes arguments from command line and locates them in PATH.
 * @cmd: The command entered by the user.
 * @str: The string entered by the user.
 * @env: The environment.
 *
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, __attribute__((unused)) char **argv, char **env) {

        pid_t pid;
        int status;
        /*char *path_to_exec;*/
        char *raw_str;
        char **exec_argv;

        if (argc != 1) {
		return 1;
        }

        while (1) {
                print_prompt();
                raw_str = read_line(0);
                exec_argv = string_split(raw_str, ' ');

                if (strcmp(exec_argv[0], "exit") == 0)
                        return 0;

                exec_argv[0] = concat_strings("/bin/",exec_argv[0]);

                if ((pid = fork()) == -1) {
                        perror("fork");
                        return 1;
                } else if (pid == 0) {
                        execve(exec_argv[0], exec_argv, env);
                } else {
                        wait(&status);
                }
        }

        return 0;
}

int str_len(char *str)
{
        int i;			/* i used as a counter */

        i = 0;			/* initialize at 0 */

        while (*str != '\0') 		/* while string isn't over */
        {
                i++;			/* increase counter */
                str++;			/* pointer arithmetic for next char */
        }

        return i;
}

int *print_prompt(){
        int i;
        char *prompt = "GreenShell$ ";

        i = 0;
        while (prompt[i] != '\0') {
                print_char(prompt[i]);
                ++i;
        }
        return 0;
}

int strcmp(char *s1, char *s2)
{
  int i = 0;
  int j = 0;
  for ( ; s1[i] != '\0'; i++)
  {
  	if (s1[j] != s2[j]) /* if chars are different, break */
	  {
	    break;
	  }
	  j++;
  }
  return(s1[j] - s2[j]); /* return difference in chars */
}
