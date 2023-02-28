#include <Arduino.h>
#include "GPS_manager/GPS_manager.hpp"
#include "position_logger/position_logger.hpp"
#include "GUI_manager/GUI_manager.hpp"

#define BTN1 (30)
#define BTN2 (31)

void systemError();

void setup() {
    if(!GUI_MAN::init()) systemError(); // initialize display, if there is an error, blink LED
    GUI_MAN::splash(); // show project splash screen
    delay(5000);
    GUI_MAN::base(); // draw screen layout

    if(!GPS_MAN::init()) { // initialize GPS module, if there is an error, draw a warning screen and blink LED
        GUI_MAN::errorMessage("GPS module error!\nCheck connection");
        systemError();
    }

    if(!POS_LOG::init()) { // initialize SD module, if there is an error, draw a warning screen and blink LED
        GUI_MAN::errorMessage("SD module error!\nCheck connection");
        systemError();
    }

    pinMode(BTN1, INPUT_PULLUP);
    pinMode(BTN2, INPUT_PULLUP);
}

void loop() {

}

/*
    blinks the built-in led forever
*/
void systemError() {
    pinMode(LED_BUILTIN, OUTPUT);
    while(true) {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(1000);
            digitalWrite(LED_BUILTIN, LOW);
            delay(1000);
        }
}