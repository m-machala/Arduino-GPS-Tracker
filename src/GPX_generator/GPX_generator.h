#ifndef GPX_GEN_H
#define GPX_GEN_H

namespace GPX_GEN {
    /*
        generates a skeleton for a GPX track
        output - amount of bytes needed to reach the center from end

    */
    int generateSkeleton(char* buffer, int bufferSize, char* creator, char* trackName);

    /*
        generates a trackpoint
    */
    void generateTrackpoint(float latitude, float longitude, float elevation, int year, int month, int day, int hour, int minute, int second);
}

#endif //GPX_GEN_H