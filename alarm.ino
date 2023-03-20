#include <Arduino.h>
#include "button.hpp"
#include "timer.hpp"
#include "led.hpp"
#include "seven_seg.hpp"

#define BUZZER_PIN 19


enum State {
    IDLE,
    CLOSING_DOOR,
    LOCKED_DOOR,
    PASSWORD1,
    PASSWORD2,
    PANIC,
};

                                 //  a   b   c   d   e   f   g
unsigned short display_ports[7] = { 32, 21, 26, 27, 14, 33, 25 };
SevenSeg segdisplay(display_ports);

Timer  timer(10000);
Timer  led_timer(500);
Button button(22);
Led    led(23);

int movement_buffer;
String inpasswd;

State state = IDLE;


void setup()
{
    timer.reset();
    led_timer.reset();
    led.clear();
    segdisplay.clear();

    ledcSetup(0, 2500, 8);
    ledcAttachPin(BUZZER_PIN, 0);

    Serial.begin(115200);
    Serial.println("Starting up...");
    delay(5000);
}


void loop()
{
    switch (state) {
    case IDLE:
        if (button.is_pressed()) {
            timer.reset();
            led_timer.reset();
            state = CLOSING_DOOR;
        }

        break;


    case CLOSING_DOOR:
        if (led_timer.count()) {
            led.toggle();
            led_timer.reset();
        }

        if (timer.count()) {
            led.clear();
            state = LOCKED_DOOR;
        }

        break;

    case LOCKED_DOOR:
        movement_buffer = analogRead(15);

        if (movement_buffer >= 2000) {
          ledcWrite(0, 50);
          delay(400);
          ledcWrite(0, 0);
          delay(400);
          ledcWrite(0, 50);
          delay(400);
          ledcWrite(0, 0);
  
          timer.reset();
          Serial.println("Please, enter your password");
          state = PASSWORD1;
        }
        
        delay(500);
        break;

    case PASSWORD1:
        segdisplay.print(timer.get_time_missing()/1000);

        inpasswd = readPassword();

        // TODO: validate password
        if (inpasswd == "foobar") {
            inpasswd = "";
            segdisplay.clear();
            state = IDLE;

        } else if (inpasswd != "") {
            timer.reset();
            segdisplay.clear();
            Serial.println("Incorrect password. Please try again.");
            state = PASSWORD2;
        }

        if (timer.count()) {
            timer.reset();
            segdisplay.clear();
            Serial.println("Incorrect password. Please try again.");
            state = PASSWORD2;
        } 

        break;

    case PASSWORD2:
        segdisplay.print(timer.get_time_missing()/1000);

        inpasswd = readPassword();

        // TODO: validate password
        if (inpasswd == "foobar") {
            inpasswd = "";
            segdisplay.clear();
            state = IDLE;

        } else if (inpasswd != "") {
            timer.reset();
            segdisplay.clear();
            ledcWrite(0, 50);
            state = PANIC;
        }

        if (timer.count()) {
            led_timer.reset();
            segdisplay.clear();
            ledcWrite(0, 50);
            state = PANIC;
        } 

        break;

    case PANIC:
        if (led_timer.count()) {
            led.toggle();
            led_timer.reset();
        }

        break;
    }
}


String readPassword()
{
    String password;
    char buff;

    while (Serial.available()) {
        buff = Serial.read();
        if (buff != '\n')
            password.concat(buff);
        delay(10);
    }

    return password;
}
