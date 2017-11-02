#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void usage(const char *app_name )
{

char *options = "\n\t[M] : M parameter means get the month which is current month minus <num> value.\
\n\t<num> : positive number for the date before the num , negative number for date which is current date plus the absolute <num> value.\n\
\ncurrent date is 20140417.\
\nfor examples:\
\n\tndays M 1\
\n\toutput: 2014 03\
\n\tndays 1\
\n\toutput: 20140416\n";

	fprintf(stderr,"Usage :	%s [M]  <num> %s", app_name , options);
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
        else
        {
                tmv->tm_mday-=atoi(argv[1]);
                timev=mktime(tmv);
                tmv=localtime(&timev);
                printf("%04d %02d %02d\n",tmv->tm_year+1900,tmv->tm_mon+1,tmv->tm_mday);
        }
}

