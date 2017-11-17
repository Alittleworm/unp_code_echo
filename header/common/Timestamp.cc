#include"Timestamp.h"
#include<sys/time.h>
#include<stdio.h>

#define __STDC_FORMAT_MACROS
#include <inttypes.h>//PRId64所在的头文件，在C++当中需要定义上面那个宏才可以使用PRId64
#undef __STDC_FORMAT_MACROS

using namespace cnmua;

//
Timestamp::Timestamp(): microSecondsSinceEpoch_(0)
{
}

Timestamp::Timestamp(int64_t microSecondSinceEpoch): microSecondsSinceEpoch_(microSecondSinceEpoch)
{
}

//获取当前的时间
Timestamp Timestamp::now()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);//这里返回一个timeval的结构体，第二个参数是一个时区，这里我们不需要返回
  int64_t seconds = tv.tv_sec;
  return Timestamp(seconds * kMicroSecondsPerSecond + tv.tv_usec);//得到的是距离19700101的微秒数的一个新的对象
}
