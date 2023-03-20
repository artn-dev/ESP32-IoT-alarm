#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <Arduino.h>


class Button {
    unsigned short port_;

public:
    Button(unsigned short port)
        : port_(port)
    {
        pinMode(port, INPUT);
    }

    bool is_pressed()
    {
        return digitalRead(port_);
    }
};

#endif /* BUTTON_HPP */