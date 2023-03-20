#ifndef TIMER_HPP
#define TIMER_HPP

#include <Arduino.h>


class Timer {
    long duration_;
    long start_time_;
    long time_missing_;

public:
    Timer(long duration)
     : duration_(duration), time_missing_(duration)
     {
        start_time_ = millis();
     }

    void reset()
    {
        time_missing_ = duration_;
        start_time_   = millis();
    }

    bool count()
    {
        unsigned long delta_time = millis() - start_time_;
        time_missing_ = duration_ - delta_time;
        return time_missing_ <= 0;
    }

    long get_time_missing()
    {
        return time_missing_;
    }
};

#endif /* TIMER_HPP */
