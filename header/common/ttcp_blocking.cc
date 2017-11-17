#include"common.h"
#include"unp.h"
#include<errno.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
static int getListenfd(uint16_t port)
{
    int listenfd = Socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    printf("listen on sockfd 1 %d\n",listenfd);
    assert(listenfd>0);

    int yes = 1;
    if(Setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)))
    {
        perror("setsockopt");
        exit(1);
    }
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (Bind(listenfd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)))
    {
	    perror("bind");
	    exit(1);
    }

    if (Listen(listenfd, 5))
    {
	    perror("listen");
	    exit(1);
    }
    return listenfd;
}
static int count;
static int acceptOrDie(int listenfd)/*retrun connfd*/
{
    struct sockaddr_in peer_addr;
    bzero(&peer_addr, sizeof(peer_addr));
    socklen_t addrlen = 0;
    int connfd = Accept(listenfd, reinterpret_cast<struct sockaddr*>(&peer_addr), &addrlen);
    if (sockfd < 0)
    {
	    perror("accept");
	    exit(1);
    }
    printf("Get Client:[%d]:[ip=%s]:[port=%d]",count++,inet_ntoa(peer_addr.sin_addr),peer_addr.sin_port);

    return connfd;

}
static int read_n(int sockfd, void* buf, int length)
{
	int nread = 0;
	while(nread < length)
	{
		ssize_t nr = ::read(sockfd,static_cast<char*>(buf) + nread, length - nread);
		if(nr > 0)
		{
			nread += static_cast<int>(nr);
		}
		else if (nr == 0)
		{
			break;//EOF
		}
		else if (errno != EINTR)
		{
			perror("read");
		}
	}
	return nread;
}

static int write_n(int sockfd, void* buf, int length)
{
	int written = 0;
	while(written < length)
	{
		ssize_t nw = ::write(sockfd,static_cast<char*>(buf) + written, length - written);
		if(nw > 0)
		{
			written += static_cast<int>(nw);
		}
		else if (nw == 0)
		{
			break;//EOF
		}
		else if (errno != EINTR)
		{
			perror("read");
		}
	}
	return written;
}


static str_echo_run(uint16_t port)
{
    int i, maxi,maxfd,listenfd,connfd,sockfd;
    int nready,client[FD_SETSIZE];
    ssize_t n;
    fd_set rset,allset;
    char buf[MAXLINE];
    socklen_t clilen;
    listenfd = getListenfd(port);
    maxfd = listenfd;
    maxi = -1;
    for(i=0; i<FD_SETSIZE; i++)
        client[i] = -1;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);
    for(;;){
        rset = allset;
        nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);

        if(FD_ISSET(listenfd, &rset)){
            connfd = acceptOrDie(listenfd);/*retrun connfd*/
            for(i = 0; i < FD_SETSIZE; i++){
                if(client[i] < 0){
                    client[i] = connfd;
                    break;
                }
            }
            if (i == FD_SETSIZE)
                err_quit("too many clients");
            FD_SET(connfd, &allset);
            if(connfd > maxfd)
                maxfd = connfd;
            if(i > maxi)
                maxi = i;
            if(--ready <=0)
                continue;
        }

        for(i = 0; i<maxi; i++){
            if( (sockfd = client[i]) < 0)
                continue;
            if(FD_ISSET(sockfd, &rset)){
                if( (n = Read(sockfd, buf, MAXLINE)) == 0){
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }else {
                    Writen(sockfd, buf, n);
                }
                if (--nready <= 0)
                    break;
            }
        }
    }
}




void transmit(const Options& opt)/*client*/
{
	struct sockaddr_in addr = resolveOrDie(opt.host.c_str(),opt.port);
	printf("cionnect ing to %s:%d\n",inet_ntoa(addr.sin_addr),opt.port);

	int sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	assert(sockfd >= 0);
	int ret = :: connect(sockfd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));
	if(ret)
	{
		perror("connect");
		printf("Unable to connect %s:%d\n",opt.host.c_str(),opt.port);
		::close(sockfd);
		return;
	}

	printf("connected\n");
    
    str_cli(stdin,sockfd);

}
void receive(const Options& opt) /*server*/
{
    str_echo_run(opt.port);
    
}



























