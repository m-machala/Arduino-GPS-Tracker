#ifndef GPX_GEN_H
#define GPX_GEN_H

namespace GPX_GEN {
    /*
        generates a skeleton for a GPX track
        buffer size should be at least 250
        output - amount of bytes needed to reach the center from end, returns 0 if there is the buffer is too small

    */
    int generateSkeleton(char* buffer, int bufferSize, const char* creator, const char* trackName);

    /*
        generates a trackpoint
        buffer size should be at least 150
        true - buffer filled successully
        false - buffer too small
    */
    bool generateTrackpoint(char* buffer, int bufferSize, float latitude, float longitude, float elevation, int year, int month, int day, int hour, int minute, int second);
}

#endif //GPX_GEN_H