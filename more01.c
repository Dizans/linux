#include <stdio.h>

#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *fp);
int see_more();

int main(int ac,char *av[])
{
    FILE *fp;
    if(ac==1)
        do_more(stdin);
    else
        while(--ac)
            if((fp=fopen(*++av,"r"))!=NULL){
                do_more(fp);
                fclose(fp);
            }
            else
                exit(1);
    return 0;
}


void do_more(FILE* fp)
{
    char line[LINELEN];
    int see_more(),reply;
    int num_of_lines=0;
    while(fgets(line,LINELEN,fp)){
        if(num_of_lines==PAGELEN){
            reply=see_more();
            if(reply==0)
                break;
            num_of_lines-=reply;
        }
        if(fputs(line,stdout)==EOF)
            exit(1);
        num_of_lines++;        
    }
}


int see_more()
{
    int c;
    while((c=getchar())!=EOF)
    {
        if(c==' ')
            return PAGELEN;
        if(c=='\n')
            return 1;
        if(c=='q')
            return 0;
    }
    return 0;
}
