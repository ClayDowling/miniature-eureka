#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int launch_program(const char *workingdir, const char *executable,
		char * const*argv)
{
	pid_t pid;
	int status;
	int died;

	switch(pid = fork()) {
	case -1:
		perror("fork");
		exit(EXIT_FAILURE);
	case 0:
		if (chdir(workingdir)) {
			perror(workingdir);
			exit(EXIT_FAILURE);
		}
		execvp(executable, argv);
	default:
		died = wait(&status);
		return status;
	}
}

int main(int argc, char **argv)
{
	char *coderace;
	char *kata;
	char *home;
	char startrace[256];
	char openfile[256];
	char * startrace_params[3];
	char * gedit_params[3];
	int status;

	home = getenv("HOME");
	coderace = getenv("CODERACE");
	kata = getenv("KATA");
	
	snprintf(startrace, sizeof(startrace), "%s/setupRace.sh", coderace);
	snprintf(openfile, sizeof(openfile), "%s/%s/src/RomanNumerals.js",
			coderace, kata);

	startrace_params[0] = startrace;
	startrace_params[1] = kata;
	startrace_params[2] = NULL;

	gedit_params[0] = "gedit";
	gedit_params[1] = "openfile";
	gedit_params[2] = NULL;

	if ((status = launch_program(coderace, startrace, startrace_params))) {
		return status;
	}
	return launch_program(home, "gedit", gedit_params);

}
