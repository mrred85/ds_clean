/**
 * @name DS Clean Utility
 * @description Delete the .DS_Store files created by OS X from specified path
 * @author Victor Rosu (victor@redpx.ro)
 * @copyright 2014
 * @version 1.0
 * @bash find / -name ".DS_Store" -depth -print -exec rm {} \;
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>

/**
 * @name Trim last slash
 * @return String
 */
char *trimLastSlash(char *str)
{
	size_t slen = strlen(str);
	if (slen > 0 && str[slen-1] == '/') {
		str[slen-1] = '\0';
	}
	return str;
}

/**
 * @name Recursive list folder
 * @return void
 */
void listFolderAndDeleteFiles(const char *dir_name, bool verbose)
{
	DIR *d;
	d = opendir(dir_name);
	if (!d) {
		fprintf(stderr, "Cannot open path '%s': %s.\nRun this command with admnistrator privileges.\n", dir_name, strerror(errno));
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		struct dirent *entry;
		const char *dname;
		
		entry = readdir(d);
		if (!entry) {
			break;
		}
		dname = entry->d_name;
		
		// Only .DS_Store files
		if (strcmp(dname, ".") != 0 && strcmp(dname, "..") != 0 && strcmp(dname, ".DS_Store") == 0) {
			// Revove file
			char fpath[PATH_MAX];
			sprintf(fpath, "%s/%s", dir_name, dname);
			remove(fpath);
			// Verbose output
			if (verbose) {
				printf("Cleaning directory: %s\n", dir_name);
			}
		}
		
		// Recursive for folders
		if (entry->d_type & DT_DIR) {
			if (strcmp(dname, ".") != 0 && strcmp(dname, "..") != 0) {
				int path_length;
				char path[PATH_MAX];
				path_length = snprintf(path, PATH_MAX, "%s/%s", dir_name, dname);
				if (path_length > PATH_MAX) {
					fprintf(stderr, "Path too long!\n");
					exit(EXIT_FAILURE);
				}
				listFolderAndDeleteFiles(path, verbose);
			}
		}
	}
	if (closedir(d)) {
		fprintf(stderr, "Could not close '%s': %s\n", dir_name, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv)
{
	char *help = "usage: ds_clean [-v] [directory...]";
	
	if (argc > 1 && argc <= 3) {
		if (strncmp(argv[1], "-h", 2) == 0) {
			printf("%s\n\n", help);
			printf(" h: Help. Print this message\n");
			printf(" v: Verbose\n");
		}
		else if (strncmp(argv[1], "-v", 2) == 0 && argv[2] != NULL && strstr(argv[2] , "/")) {
			listFolderAndDeleteFiles(trimLastSlash(argv[2]), true);
		}
		else if (strstr(argv[1], "/")) {
			listFolderAndDeleteFiles(trimLastSlash(argv[1]), false);
		}
		else {
			printf("%s\n", help);
		}
	}
	else {
		printf("%s\n", help);
	}
	return 0;
}
