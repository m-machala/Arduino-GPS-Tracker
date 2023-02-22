#include "position_logger.hpp"
#include "../SD_manager/SD_manager.hpp"
#include "../GPX_generator/GPX_generator.hpp"

int seekBackValue = 0;

bool POS_LOG::startLogging(const char* creator, const char* trackName) {
    int count = 0;
    char fileName[13] = "0.gpx";
    
    // find the next available file name
    while(!SD_MAN::fileExists(fileName)) {
        count++;
        sprintf(fileName, "%d.gpx", count);

        if(count > 99999999) {
            return false;
        }
    }

    if(!SD_MAN::openFileWrite(fileName)) {
        return false;
    }

    int bufferSize = 250;
    char buffer[bufferSize];
    seekBackValue = GPX_GEN::generateSkeleton(buffer, bufferSize, creator, trackName);
    if(seekBackValue == 0) {
        return false;
    }

    SD_MAN::fileWrite(buffer);
    SD_MAN::fileFlush();

    return true;
}

bool POS_LOG::addTrackpoint(float latitude, float longitude, float elevation, int year, int month, int day, int hour, int minute, int second) {
    int bufferSize = 150;
    char buffer[bufferSize];

    if(!GPX_GEN::generateTrackpoint(buffer, bufferSize, latitude, longitude, elevation, year, month, day, hour, minute, second)) {
        return false;
    }
    SD_MAN::fileWrite(buffer);
    SD_MAN::fileFlush();
    return true;
}

void POS_LOG::stopLogging() {
    SD_MAN::fileClose();
}