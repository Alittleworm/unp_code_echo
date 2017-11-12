#include"common.h"
#include<assert.h>
#include<errno.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"Timestamp.h"
static int acceptOrDie(uint16_t port)
{
    int listenfd = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    printf("listen on sockfd 1 %d\n",listenfd);
    assert(listenfd>0);

    int yes = 1;
    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)))
    {
        perror("setsockopt");
        exit(1);
    }
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(listenfd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)))
    {
	    perror("bind");
	    exit(1);
    }

    if (listen(listenfd, 5))
    {
	    perror("listen");
	    exit(1);
    }

    struct sockaddr_in peer_addr;
    bzero(&peer_addr, sizeof(peer_addr));
    socklen_t addrlen = 0;
    printf("listen on sockfd %d\n",listenfd);
    int sockfd = ::accept(listenfd, reinterpret_cast<struct sockaddr*>(&peer_addr), &addrlen);
    if (sockfd < 0)
    {
	    perror("accept");
	    exit(1);
    }
    ::close(listenfd);
    return sockfd;

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
void transmit(const Options& opt)
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
void receive(const Options& opt)
{
    int sockfd = acceptOrDie(opt.port);
    printf("read sockfd = %d\n",sockfd);
    str_echo(sockfd);
    
}



























