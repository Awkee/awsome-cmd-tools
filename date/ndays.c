#include <stdio.h>
#include <time.h>


#define LF                  (uint8_t) 10
#define CR                  (uint8_t) 13
#define CRLF                "\x0d\x0a"
#define CRLF_LEN            (sizeof("\x0d\x0a") - 1)


void usage( const char *app_name )
{
char *options[] = {
    "Usage:%s [M number ]  [ T timestamp ] [ S start_datetime duration ] [ number] " CRLF
    ,"" CRLF
    ,"Options:" CRLF
    ,"   number                      :   获取 number 前的日期，格式 'YYYY MM DD'"CRLF
    ,"   M number                    :   获取 number 前的月份，格式 'YYYY MM'"CRLF
    ,"   T timestamp                 :   将时间戳数值转换成本地时间，格式 'YYYY MM DD HH MI SS'"CRLF
    ,"   S start_datetime duration   :   获取设定起始时间经过一定时长后的结束时间值 ， 格式 'YYYY MM DD HH MI SS'"CRLF
    ,"   s start_datetime duration   :   获取设定起始时间经过一定时长后的结束时间值 ， 格式 'YYYYMMDDHHMISS'"CRLF
    ,""CRLF
    ,NULL
};

    int i = 0;
    while ( options[i] != NULL )
    {
        fprintf( stderr , "%s", options[i++]);
    }
}

int main(int argc,char **argv)
{
        time_t timev;
        struct tm *tmv;
        if(1==argc)
        {
                usage( argv[0] );
                return 1;
        }
        timev=time(NULL);
        tmv=localtime(&timev);
        if('M'==argv[1][0])
        {
                tmv->tm_mday=1;
                tmv->tm_mon-=atoi(argv[2]);
                timev=mktime(tmv);
                tmv=localtime(&timev);
                printf("%04d %02d\n",tmv->tm_year+1900,tmv->tm_mon+1);
        }
        else if( 'T' == argv[1][0] )
        {
                timev = atol( argv[2]);
                tmv=localtime(&timev);
                printf("%04d %02d %02d %02d %02d %02d\n",tmv->tm_year+1900,tmv->tm_mon+1,tmv->tm_mday, tmv->tm_hour, tmv->tm_min, tmv->tm_sec );
                
        }
        else if( 'S' == argv[1][0] )
        {
                sscanf( argv[2] , "%04d%02d%02d%02d%02d%02d", & tmv->tm_year , & tmv->tm_mon ,& tmv->tm_mday , & tmv->tm_hour , & tmv->tm_min , & tmv->tm_sec );
                tmv->tm_year -= 1900;
                tmv->tm_mon  --;
                tmv->tm_sec+=atoi(argv[3]);
                timev=mktime(tmv);
                tmv=localtime(&timev);
                printf("%04d %02d %02d %02d %02d %02d\n",tmv->tm_year+1900,tmv->tm_mon+1,tmv->tm_mday, tmv->tm_hour, tmv->tm_min, tmv->tm_sec );
        }
        else if( 's' == argv[1][0] )
        {
                sscanf( argv[2] , "%04d%02d%02d%02d%02d%02d", & tmv->tm_year , & tmv->tm_mon ,& tmv->tm_mday , & tmv->tm_hour , & tmv->tm_min , & tmv->tm_sec );
                tmv->tm_year -= 1900;
                tmv->tm_mon  --;
                tmv->tm_sec+=atoi(argv[3]);
                timev=mktime(tmv);
                tmv=localtime(&timev);
                printf("%04d%02d%02d%02d%02d%02d\n",tmv->tm_year+1900,tmv->tm_mon+1,tmv->tm_mday, tmv->tm_hour, tmv->tm_min, tmv->tm_sec );
        }
        else
        {
                tmv->tm_mday-=atoi(argv[1]);
                timev=mktime(tmv);
                tmv=localtime(&timev);
                printf("%04d %02d %02d\n",tmv->tm_year+1900,tmv->tm_mon+1,tmv->tm_mday);
        }
}


