/*************************************************************************
  > File Name: lst.c
  > Author: zwker
  > Mail: xiaoyu0720@gmail.com 
  > Created Time: 2016年11月01日 星期二 20时59分13秒
 ************************************************************************/

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char *usage_opts[] = {
"Usage:",
"	lst  [path]",
"Brief:",
"	a tool for list your path structure",
NULL
};

void usage(){
	char **p = usage_opts;
	while( *p != NULL )
	{
		fprintf( stderr, "%s\n", *p++ );
	}
}

int listdir(const char *name, int level)
{
	DIR *dir;
	struct dirent *entry;

	if (!(dir = opendir(name)))
		return 1;
	if (!(entry = readdir(dir)))
		return 2;

	do {
		if (entry->d_type == DT_DIR) {
			char path[1024];
			int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
			path[len] = 0;
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			printf("%*s[%s]\n", level*2, "", entry->d_name);
			listdir(path, level + 1);
		}
		else
			printf("%*s- %s\n", level*2, "", entry->d_name);
	} while (entry = readdir(dir));
	closedir(dir);
	return 0;
}


int main(int argc, char *argv[])
{
	int arg;
	if (argc < 2) {

		if (listdir(".", 0)) {
			fprintf(stderr, "%s.\n", strerror(errno));
			return -1;
		}

	} else {

		for (arg = 1; arg < argc; arg++) {
			if (listdir(argv[arg],0)) {
				fprintf(stderr, "%s.\n", strerror(errno));
				return -1;
			}
		}

	}
	return 0;
}


