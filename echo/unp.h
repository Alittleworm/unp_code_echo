#define MAXLINE 8192
#include<readline1.c>
#include<header.h>
#define MAXLINE 8192
int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,struct timeval *timeout);
void str_echo(int sockfd);
void str_cli(FILE* fp,int sockfd);
void str_cli_select(FILE* fp,int sockfd);
void error_quit(char *fmt, ...);
