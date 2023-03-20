#ifndef SEVEN_SEG_HPP
#define SEVEN_SEG_HPP

#include <Arduino.h>


constexpr static unsigned short SEGMENTS[10][7] = {
//    a  b  c  d  e  f  g
    { 1, 1, 1, 1, 1, 1, 0 }, // 0
    { 0, 1, 1, 0, 0, 0, 0 }, // 1
    { 1, 1, 0, 1, 1, 0, 1 }, // 2
    { 1, 1, 1, 1, 0, 0, 1 }, // 3
    { 0, 1, 1, 0, 0, 1, 1 }, // 4
    { 1, 0, 1, 1, 0, 1, 1 }, // 5
    { 1, 0, 1, 1, 1, 1, 1 }, // 6
    { 1, 1, 1, 0, 0, 0, 0 }, // 7
    { 1, 1, 1, 1, 1, 1, 1 }, // 8
    { 1, 1, 1, 0, 0, 1, 1 }  // 9
};

class SevenSeg {
    unsigned short ports_[7];

public:
    SevenSeg(unsigned short ports[7])
    {
        ports_[0] = ports[0];
        ports_[1] = ports[1];
        ports_[2] = ports[2];
        ports_[3] = ports[3];
        ports_[4] = ports[4];
        ports_[5] = ports[5];
        ports_[6] = ports[6];
        
        pinMode(ports_[0], OUTPUT);
        pinMode(ports_[1], OUTPUT);
        pinMode(ports_[2], OUTPUT);
        pinMode(ports_[3], OUTPUT);
        pinMode(ports_[4], OUTPUT);
        pinMode(ports_[5], OUTPUT);
        pinMode(ports_[6], OUTPUT);
    }

    void print(unsigned short n)
    {
        digitalWrite(ports_[0], SEGMENTS[n][0]);
        digitalWrite(ports_[1], SEGMENTS[n][1]);
        digitalWrite(ports_[2], SEGMENTS[n][2]);
        digitalWrite(ports_[3], SEGMENTS[n][3]);
        digitalWrite(ports_[4], SEGMENTS[n][4]);
        digitalWrite(ports_[5], SEGMENTS[n][5]);
        digitalWrite(ports_[6], SEGMENTS[n][6]);
    }

    void clear()
    {
        digitalWrite(ports_[0], LOW);
        digitalWrite(ports_[1], LOW);
        digitalWrite(ports_[2], LOW);
        digitalWrite(ports_[3], LOW);
        digitalWrite(ports_[4], LOW);
        digitalWrite(ports_[5], LOW);
        digitalWrite(ports_[6], LOW);
    }
};

#endif /* SEVEN_SEG_HPP */
