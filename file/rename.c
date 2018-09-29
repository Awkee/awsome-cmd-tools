/*************************************************************************
  > File Name: rename.c
  > Brief  :  a tool for rename files in the same file system
  > Author: zwker
  > Mail: xiaoyu0720@gmail.com 
  > Created Time: 2017年10月30日 星期一 17时15分45秒
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_SIZE 1024
#define LEN_PRE 256

char *usage_opts[] = {
	"usage:",
	"    rename -i <src_dir>  [ -o <out_dir> ]  [-d N] [-s <prefix>] [-a <append>]",
	"Descript:",
	"	文件名快速替换工具",
	"params:",
		"    -i <src_dir> : 入口目录, 默认为当前目录\".\"",
	"    -o <out_dir> : 出口目录, 默认为当前目录\".\"",
	"    -d N         : 删除文件名长度为N位的后缀部分",
	"    -s <prefix>  : 替换文件名前缀，替换长度与prefix字符串长度相同",
	"    -a <append>  : 追加前缀为append的字符串",
	NULL
};


void usage()
{
	char **p = usage_opts;
	while( *p != NULL )
	{
		fprintf( stderr, "%s\n", *p );
		p++;
	}
}

int main(int argc, char *argv[])
{

	int     i,ret, opt;
	char    old_name[MAX_SIZE],new_name[MAX_SIZE],tmp_name[MAX_SIZE], tmp2_name[MAX_SIZE];
	DIR     *dp;
	struct  dirent     *dirp;

	char in_dir[MAX_SIZE] , out_dir[MAX_SIZE];
	char str_prefix[LEN_PRE], str_append[ LEN_PRE] , str_sub[LEN_PRE]; 
	int flag_del , flag_append, flag_sub , len_del ;

	memset(in_dir, 0, sizeof(in_dir));
	strcpy( in_dir, ".");
	strcpy( out_dir, ".");
	flag_del = 0;  //删除标识
	flag_append = 0;// 追加标识
	flag_sub = 0; // 替换标识
	while ((opt = getopt(argc, argv, "a:d:i:o:s:")) != -1) 
	{
		switch (opt) {
			case 'i':
				memset( in_dir, 0, sizeof(in_dir));
				strcpy( in_dir , optarg );
				break;
			case 'o':
				memset( out_dir, 0, sizeof(out_dir));
				strcpy( out_dir , optarg );
				break;
			case 'd':
				len_del = atoi(optarg);
				flag_del = 1;
				break;
			case 's':
				memset( str_sub, 0, sizeof(str_sub) );
				strcpy( str_sub , optarg);
				flag_sub = 1;
				break;
			case 'a':
				memset( str_append, 0, sizeof(str_append) );
				strcpy( str_append , optarg);
				flag_append = 1;
				break;
			default: /* '?' */
				usage();
				exit(EXIT_FAILURE);
		}
	}

	if( flag_sub == 0 && flag_del  == 0 && flag_append == 0 )
	{
		usage();
		exit(0);
	}

	if ( (dp = opendir(in_dir)) == NULL)
	{
		perror("operdir error");
		exit(0);
	}

	int old_len = 0;
	while ( (dirp = readdir(dp)) != NULL)
	{
		if( strcmp( dirp->d_name ,"." ) == 0 || strcmp( dirp->d_name ,".." ) == 0 )
			continue;
		memset(old_name, 0 , sizeof(old_name));
		sprintf(old_name, "%s/%s", in_dir, dirp->d_name );

		memset(new_name, 0 , sizeof(new_name));
		memset(tmp_name, 0 , sizeof(tmp_name));
		memset(tmp2_name, 0 , sizeof(tmp2_name));
		if( flag_del == 1 )
			strncpy( tmp_name , dirp->d_name , strlen(dirp->d_name) - len_del);
		else
			strncpy( tmp_name , dirp->d_name , strlen(dirp->d_name) );

		if( flag_sub == 1)
			for( i = 0 ; i < strlen( str_sub) ; i++) tmp_name[i] = str_sub[i]; 
		if( flag_append == 1)
			sprintf( new_name, "%s/%s%s", out_dir , str_append , tmp_name );
		else
			sprintf( new_name, "%s/%s", out_dir , tmp_name );
		ret = rename(old_name , new_name );
		if ( ret != 0 )
			perror( " rename error!\n");
		printf("rename %s %s \n", old_name , new_name );
	}


	closedir(dp);


	exit(0);
}

