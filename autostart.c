/* See LICENSE file for copyright and license details. */
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "autostart.h"

static char *
scriptpath(const char *base, const char *directory, const char *name)
{
	char *path;
	size_t size;

	if (!base || !*base)
		return NULL;
	size = strlen(base) + strlen(directory) + strlen(name) + 3;
	if (!(path = malloc(size)))
		return NULL;
	snprintf(path, size, "%s/%s/%s", base, directory, name);
	return path;
}

static char *
findscript(const char *name)
{
	const char *home = getenv("HOME");
	const char *config = getenv("XDG_CONFIG_HOME");
	const char *data = getenv("XDG_DATA_HOME");
	const char *bases[3], *directories[3];
	char *path;
	struct stat sb;
	unsigned int i;

	/* XDG base directories must be absolute; empty/relative values are ignored. */
	bases[0] = config && config[0] == '/' ? config : home;
	directories[0] = config && config[0] == '/' ? "dwm" : ".config/dwm";
	bases[1] = data && data[0] == '/' ? data : home;
	directories[1] = data && data[0] == '/' ? "dwm" : ".local/share/dwm";
	bases[2] = home;
	directories[2] = ".dwm";

	for (i = 0; i < 3; i++) {
		path = scriptpath(bases[i], directories[i], name);
		if (!path)
			continue;
		if (stat(path, &sb) == 0 && S_ISREG(sb.st_mode) && access(path, X_OK) == 0)
			return path;
		free(path);
	}
	return NULL;
}

static void
runscript(const char *path, int blocking, int displayfd)
{
	struct sigaction action, previous;
	pid_t pid;

	memset(&action, 0, sizeof action);
	sigemptyset(&action.sa_mask);
	action.sa_handler = SIG_DFL;
	/* dwm ignores SIGCHLD; blocking scripts still need a waitable child. */
	if (blocking && sigaction(SIGCHLD, &action, &previous) < 0) {
		perror("dwm: autostart sigaction");
		return;
	}
	pid = fork();
	if (pid == 0) {
		if (displayfd >= 0)
			close(displayfd);
		sigaction(SIGCHLD, &action, NULL);
		/* No shell command construction: spaces and metacharacters stay literal. */
		execl(path, path, (char *)NULL);
		fprintf(stderr, "dwm: cannot execute %s: %s\n", path, strerror(errno));
		_exit(EXIT_FAILURE);
	}
	if (pid < 0)
		perror("dwm: autostart fork");
	else if (blocking)
		while (waitpid(pid, NULL, 0) < 0 && errno == EINTR)
			;
	if (blocking)
		sigaction(SIGCHLD, &previous, NULL);
}

void
runautostart(int displayfd)
{
	char *path;

	path = findscript("autostart_blocking.sh");
	if (path) {
		runscript(path, 1, displayfd);
		free(path);
	}
	path = findscript("autostart.sh");
	if (path) {
		runscript(path, 0, displayfd);
		free(path);
	}
}
