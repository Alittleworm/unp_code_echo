#include<boost/program_options.hpp>
#include<iostream>
#include<netdb.h>
#include<stdio.h>
#include"common.h"

namespace po = boost::program_options;
bool parseCommandLine(int argc, char* argv[], Options* opt)
{
  po::options_description desc("Allowed options");
  desc.add_options()
      ("help,h", "Help")
      ("port,p", po::value<uint16_t>(&opt->port)->default_value(5001), "TCP port")
      ("length,l", po::value<int>(&opt->length)->default_value(65536), "Buffer length")
      ("number,n", po::value<int>(&opt->number)->default_value(8192), "Number of buffers")
      ("trans,t",  po::value<std::string>(&opt->host), "Transmit")
      ("recv,r", "Receive")
      ("nodelay,D", "set TCP_NODELAY")
      ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  opt->transmit = vm.count("trans");
  opt->receive = vm.count("recv");
  opt->nodelay = vm.count("nodelay");
  if (vm.count("help"))
  {
    std::cout << desc << std::endl;
    return false;
  }

  if (opt->transmit == opt->receive)
  {
    printf("either -t or -r must be specified.\n");
    return false;
  }

  printf("port = %d\n", opt->port);
  if (opt->transmit)
  {
    printf("buffer length = %d\n", opt->length);
    printf("number of buffers = %d\n", opt->number);
  }
  else
  {
    printf("accepting...\n");
  }
  return true;
}
//#pragma GCC diagnostic ignored "-Wold-style-cast"

struct sockaddr_in resolveOrDie(const char* host, uint16_t port)
{
  struct hostent* he = ::gethostbyname(host);
  if (!he)
  {
    perror("gethostbyname");
    exit(1);
  }
  assert(he->h_addrtype == AF_INET && he->h_length == sizeof(uint32_t));
  struct sockaddr_in addr;
  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr = *reinterpret_cast<struct in_addr*>(he->h_addr);
  return addr;
}

void str_cli(FILE *fp, int sockfd)
{
    int maxfdp1,stdineof;
    fd_set rset;
    char buf[MAXLINE];
    int n;

    stdineof = 0;
    FD_ZERO(&rset);
    for(;;){
        if(stdineof == 0)
            FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        Select(maxfdp1, &rset, NULL, NULL, NULL);
        if(FD_ISSET(sockfd, &rset)){//socket is readable
            if( (n = Read(sockfd)) == 0){
                if(stdineof == 1)
                    return; //no more msg
                else
                    err_quit("str_cli: server terminated premayurely");
            }
            Write(fileno(stdout), buf, n);
        }

        if(FD_ISSET(fileno(fp), &rset)){// input is readable
            if( (n = Read(fileno(fp), buf, MAXLINE)) == 0){
                stdineof = 1;
                Shutdown(fileno(fp), &rset);
                continue;
            }
            Writen(sockfd, buf, n);
        }
    }
}





