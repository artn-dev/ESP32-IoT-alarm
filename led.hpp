#ifndef LED_HPP
#define LED_HPP

#include <Arduino.h>


class Led {
    unsigned short port_;
    unsigned short state_;

public:
    Led(unsigned short port)
        : port_(port)
    {
        pinMode(port, OUTPUT);
        clear();
    }

    void clear()
    {
        state_ = LOW;
        digitalWrite(port_, state_);
    }

    void toggle()
    {
        state_ = !state_;
        digitalWrite(port_, state_);
    }
};

#endif /* LED_HPP */
