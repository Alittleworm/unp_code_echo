#ifndef __BASE_TIMESTAMP_H__
#define __BASE_TIMESTAMP_H__

#include<iostream>
#include"common.h"

namespace cnmua
{

class Timestamp
{
public:
    Timestamp();
    explicit Timestamp(int64_t microSecondSinceEpoch);
    //void swap(Timestamp& that);
    static Timestamp now();
    static const int kMicroSecondsPerSecond = 1000*1000;
    int64_t microSecondsSinceEpoch(){return microSecondsSinceEpoch_;};
private:
    int64_t microSecondsSinceEpoch_;
}; 

inline double timeDifference(Timestamp high, Timestamp low)
{
    int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
    return static_cast<double>(diff) / Timestamp::kMicroSecondsPerSecond;
}

}

#endif
