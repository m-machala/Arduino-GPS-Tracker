#include <Arduino.h>
#include "GPS_manager/GPS_manager.hpp"
#include "position_logger/position_logger.hpp"
#include "GUI_manager/GUI_manager.hpp"

#define BTN1 (30)
#define BTN2 (31)

void systemError();
bool readButton(int button);

enum State { STARTING, NOFIX, TRACKING, WAITING, ENDING };
State state = STARTING;
unsigned long timer = 0;
char creator[] = "Martin Machala - https://github.com/m-machala";

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

    // init buttons
    pinMode(BTN1, INPUT_PULLUP);
    pinMode(BTN2, INPUT_PULLUP);

    GUI_MAN::startScreen();
}

void loop() {
    GPS_MAN::update();
    GUI_MAN::time(GPS_MAN::getHour(), GPS_MAN::getMinute());
    GUI_MAN::date(GPS_MAN::getYear(), GPS_MAN::getMonth(), GPS_MAN::getSecond());
    GUI_MAN::satCount(GPS_MAN::getSats());

    switch(state) {
        // starting info screen, tests for a button press, if there is no data, show an info screen
        case STARTING:
            if(readButton(BTN1)) {
                // give an info message in case of no GPS data available
                if(!GPS_MAN::fix()) {
                    timer = millis();
                    state = NOFIX;
                    GUI_MAN::infoMessage("No GPS signal!\nPlease wait,\nthen try again");
                }
                else {
                    if(!POS_LOG::startLogging(creator)) {
                        GUI_MAN::errorMessage("SD error!");
                        systemError();
                    }
                    state = TRACKING;
                }
            }
            break;

        // waits for 5 seconds, then goes back to STARTING
        case NOFIX:
            if(millis() - timer >= 5000) {
                state = STARTING;
                GUI_MAN::startScreen();
            }
            break;

        case TRACKING:
            break;

        case WAITING:
            break;

        case ENDING:
            break;

        default:
            break;
    }

    delay(100);
}

/*
    blinks built-in led forever
*/
void systemError() {
    pinMode(LED_BUILTIN, OUTPUT);
    while(true) {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(2000);
            digitalWrite(LED_BUILTIN, LOW);
            delay(2000);
        }
}

/*
    reads the state of a given button
    true - button is pressed
    false - button is not pressed
*/
bool readButton(int button) {
    if(digitalRead(button) == LOW) {
        // debounce
        delay(10);
        if(digitalRead(button) == LOW) return true;
    }
    return false;
}