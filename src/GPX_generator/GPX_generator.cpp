#include "GPX_generator.h"
#include <stdio.h>

int generateSkeleton(char* buffer, int bufferSize, char* creator, char* trackName) {
    if(bufferSize < 250) return 0; // 250 chosen based on the format string's length

    sprintf(buffer, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<gpx xmlns=\"http://www.topografix.com/GPX/1/1\" version=\"1.1\" creator=\"%s\">\n\t<trk>\n\t\t<name>%s</name>\n\t\t<trkseg>\n\n\t\t</trkseg>\n\t</trk>\n</gpx>", creator, trackName);
    return 27; // there are 27 characters between the space where new data can be inserted and the end
}

bool generateTrackpoint(char* buffer, int bufferSize, float latitude, float longitude, float elevation, int year, int month, int day, int hour, int minute, int second) {
    if(bufferSize < 150) return false; // 150 chosen based on the format string's length

    sprintf(buffer, "\t\t\t<trkpt lat=\"%f\" lon=\"%f\">\n\t\t\t\t<ele>%f</ele>\n\t\t\t\t<time>%d-%d-%dT%d:%d:%dZ</time>\n\t\t\t</trkpt>\n", latitude, longitude, elevation, year, month, day, hour, minute, second);
    return true;
}