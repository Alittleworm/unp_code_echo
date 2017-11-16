#include "unp.h"
#include<sys/select.h>
int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
       struct timeval *timeout)
{
    int  n;
    if ( (n = select(nfds, readfds, writefds, exceptfds, timeout)) < 0)
        err_sys("select error");
    return(n);  /* can return 0 on timeout */
}
void error_quit(char *fmt, ...)    
{    
    int res;    
    va_list list;    
    va_start(list, fmt);    
    res = vfprintf(stderr, fmt, list);    
    if( errno != 0 )    
        fprintf(stderr, " : %s", strerror(errno));    
    fprintf(stderr, "\n", list);    
    va_end(list);    
    exit(1);    
}
void str_echo(int sockfd){
    ssize_t n;
    char buf[4096];
again:
    while((n = read(sockfd,buf,4096))>0){

        fputs(buf,stdout);
        if(write(sockfd,buf,strlen(buf))<0){
            perror("write!");
            return ;
        }
        memset(buf,0,sizeof(buf));
    }
}
void str_cli(FILE* fp,int sockfd)
{
    char sendline[MAXLINE],recvline[MAXLINE];
    while(fgets(sendline,MAXLINE,fp)!=NULL){
        write(sockfd,sendline,strlen(sendline));
        if(read(sockfd,recvline,MAXLINE)==0)
            return;
    }
}

void str_cli_select(FILE* fp,int sockfd)
{
    int maxfdp1;
    fd_set rset;
    char sendline[MXALINE], recvline[MAXLINE];

    FD_ZERO(&rest);
    for(;;){
        FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        select(maxfdp1, &rset,NULL,NULL,NULL);


    }
}
