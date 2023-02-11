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

void GPS_MAN::getTimeReadable(char* buffer, int size) {
    if(size < 6) {
        return;
    }

    char* time = "00:00";
    time[0] = '0' + GPS.hour / 10;
    time[1] = '0' + GPS.hour % 10;
    time[3] = '0' + GPS.minute / 10;
    time[4] = '0' + GPS.minute % 10;
    
    strcpy(buffer, time);
}

void GPS_MAN::getDateReadable(char* buffer, int size) {
    if(size < 9) {
        return;
    }

    char* date = "00.00.00";
    date[0] = '0' + GPS.day / 10;
    date[1] = '0' + GPS.day % 10;
    date[3] = '0' + GPS.month / 10;
    date[6] = '0' + GPS.year / 10;
    date[7] = '0' + GPS.year % 10;
    strcpy(buffer, '\0');
}