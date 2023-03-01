#include "GPS_manager.hpp"

//static Adafruit_GPS GPS(&Serial1);

bool GPS_MAN::init() {
    bool result = GPS.begin(9600);
    // set update rate to 1Hz
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

    return result;
}

bool GPS_MAN::update() {
    GPS.read();

    while(GPS.newNMEAreceived()) {
        // test if the sentence can be parsed
        if(!GPS.parse(GPS.lastNMEA())) {
            // sentence cannot be parsed
            continue;
        }
        // sentence parsed successfully
        return true;
    }
    return false;
}

bool GPS_MAN::fix() {
    return GPS.fix;
}

int GPS_MAN::getSats() {
    return GPS.satellites;
}

float GPS_MAN::getLon() {
    return GPS.longitude / 100;
}

float GPS_MAN::getLat() {
    return GPS.latitude / 100;
}

float GPS_MAN::getAlt() {
    return GPS.altitude;
}

int GPS_MAN::getHour() {
    return GPS.hour;
}

int GPS_MAN::getMinute() {
    return GPS.minute;
}

int GPS_MAN::getSecond() {
    return GPS.seconds;
}

int GPS_MAN::getYear() {
    return GPS.year;
}

int GPS_MAN::getMonth() {
    return GPS.month;
}

int GPS_MAN::getDay() {
    return GPS.day;
}