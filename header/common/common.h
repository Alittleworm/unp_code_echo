#ifndef _COMM_H__
#define _COMM_H__

#include <string>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
typedef signed char int8_t;
typedef short  int int16_t;
typedef int    int32_t;

#if __WORDSIZE == 64
typedef long int int64_t;
#else
__extension__
typedef long long int int64_t;
#endif


struct Options
{
  uint16_t port;
  int length;
  int number;
  bool transmit, receive, nodelay;
  std::string host;
  Options()
    : port(0), length(0), number(0),
      transmit(false), receive(false), nodelay(false)
  {
  }
};

bool parseCommandLine(int argc, char* argv[], Options* opt);
struct sockaddr_in resolveOrDie(const char* host, uint16_t port);

struct SessionMessage
{
  int32_t number;
  int32_t length;
} __attribute__ ((__packed__));

struct PayloadMessage
{
  int32_t length;
  char data[0];
};

void transmit(const Options& opt);

void receive(const Options& opt);

void str_cli(FILE *fp, int sockfd);
#endif
