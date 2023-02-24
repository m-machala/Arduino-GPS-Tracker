#include "GPS_manager.hpp"

//static Adafruit_GPS GPS(&Serial1);

void GPS_MAN::init() {
    GPS.begin(9600);
    // set update rate to 1Hz
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
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
    return GPS.longitude;
}

float GPS_MAN::getLat() {
    return GPS.latitude;
}

float GPS_MAN::getAlt() {
    return GPS.altitude;
}