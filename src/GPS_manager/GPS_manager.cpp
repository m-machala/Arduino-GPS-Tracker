#include "GPS_manager.hpp"

//static Adafruit_GPS GPS(&Serial1);

void GPS_MAN::init() {
  GPS.begin(9600);
    // set mode
    //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    // set update rate to 1Hz
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

    //GPS.sendCommand(PGCMD_ANTENNA);

    //delay(1000);

    //GPS.sendCommand(PMTK_Q_RELEASE);
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

int GPS_MAN::getSats() {
    return(GPS.satellites);
}

float GPS_MAN::getLon() {
    return(GPS.longitude);
}

float GPS_MAN::getLat() {
    return(GPS.latitude);
}

float GPS_MAN::getAlt() {
    return(GPS.altitude);
}

char* GPS_MAN::getTimeReadable() {
    char* time = new char[7];
    strcpy(time, "00:00");
    time[0] = '0' + GPS.hour / 10;
    time[1] = '0' + GPS.hour % 10;
    time[3] = '0' + GPS.minute / 10;
    time[4] = '0' + GPS.minute % 10;
    return time;
}

char* GPS_MAN::getDateReadable() {
    char* date = new char[9];
    strcpy(date, "00.00.00");
    date[0] = '0' + GPS.day / 10;
    date[1] = '0' + GPS.day % 10;
    date[3] = '0' + GPS.month / 10;
    date[6] = '0' + GPS.year / 10;
    date[7] = '0' + GPS.year % 10;
    return date;

    //return "00.00.00";
}