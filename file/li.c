#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[])
{
        int     i;
        char    path[256];
        DIR     *dp;
        struct  dirent     *dirp;

        if (argc == 1) {
                if ( (dp = opendir(".")) == NULL)
                {
                        perror("operdir error");
                        exit(1);
                }

                readdir(dp);
                readdir(dp);

                while ( (dirp = readdir(dp)) != NULL)
                        printf("%s\n", dirp->d_name);

                closedir(dp);

                exit(0);
        }

        for (i = 1; i < argc; i++) {
                memset(path, 0, sizeof(path));
                strcpy(path, argv[i]);

                if ( (dp = opendir(path)) == NULL)
                {
                        perror("operdir error");
                        continue;
                }

                readdir(dp);
                readdir(dp);

                while ( (dirp = readdir(dp)) != NULL)
                        printf("%s/%s\n", path, dirp->d_name);

                closedir(dp);
        }
        exit(0);

}

