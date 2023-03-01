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
unsigned long minutesSinceStart = 0;
int lastMinutes = 0;
int kmTraveled = 0;
int meters = 0;
float lastLat = 0;
float lastLon = 0;
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
    bool newData = GPS_MAN::update();
    if(newData) {
        GUI_MAN::time(GPS_MAN::getHour(), GPS_MAN::getMinute());
        GUI_MAN::date(GPS_MAN::getYear(), GPS_MAN::getMonth(), GPS_MAN::getSecond());
        GUI_MAN::satCount(GPS_MAN::getSats());
    }

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
                    minutesSinceStart = 0;
                    meters = 0;
                    kmTraveled = 0;
                    lastMinutes = GPS_MAN::getMinute() + (GPS_MAN::getHour() * 60);
                    lastLat = GPS_MAN::getLat();
                    lastLon = GPS_MAN::getLon();
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

        // tests if new data is available and if fix is available; if yes, log new data
        case TRACKING:
            int currentMinutes = GPS_MAN::getMinute() + (GPS_MAN::getHour() * 60);
            if(lastMinutes < currentMinutes) {
                minutesSinceStart = currentMinutes - lastMinutes;
            }
            else if(lastMinutes > 1000 && currentMinutes < 500) {
                int modifiedMinutes = lastMinutes + 1440; // 60 * 24
                minutesSinceStart = modifiedMinutes - lastMinutes;
            }
            lastMinutes = currentMinutes;
            
            if(newData && GPS_MAN::fix()) {
                POS_LOG::addTrackpoint(GPS_MAN::getLon(), GPS_MAN::getLat(), GPS_MAN::getAlt(), GPS_MAN::getYear(), GPS_MAN::getMonth(), GPS_MAN::getDay(), GPS_MAN::getHour(), GPS_MAN::getMinute(), GPS_MAN::getSecond());
                GUI_MAN::trackingScreen(minutesSinceStart / 60, minutesSinceStart % 60, GPS_MAN::getLat(), GPS_MAN::getLon(), false);
            }
            if(readButton(BTN1)) {
                GUI_MAN::trackingScreen(minutesSinceStart / 60, minutesSinceStart % 60, GPS_MAN::getLat(), GPS_MAN::getLon(), true);
                state = WAITING;
            } 
            break;

        case WAITING:
            lastMinutes = GPS_MAN::getMinute() + (GPS_MAN::getHour() * 60);

            if(readButton(BTN1)) {
                state = TRACKING;
            }

            if(readButton(BTN2)) {
                state = ENDING;
            }
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