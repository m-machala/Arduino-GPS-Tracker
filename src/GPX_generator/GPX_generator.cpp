#include "GPX_generator.hpp"
#include <stdio.h>
#include <stdlib.h>

int GPX_GEN::generateSkeleton(char* buffer, int bufferSize, const char* creator, const char* trackName) {
    if(bufferSize < 250) return 0; // 250 chosen based on the format string's length

    sprintf(buffer, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<gpx xmlns=\"http://www.topografix.com/GPX/1/1\" version=\"1.1\" creator=\"%s\">\n\t<trk>\n\t\t<name>%s</name>\n\t\t<trkseg>\n\n\t\t</trkseg>\n\t</trk>\n</gpx>", creator, trackName);
    return 27; // number of bytes between the space where new data can be inserted and the end
}

bool GPX_GEN::generateTrackpoint(char* buffer, int bufferSize, float latitude, float longitude, float elevation, int year, int month, int day, int hour, int minute, int second) {
    if(bufferSize < 150) return false; // 150 chosen based on the format string's length
    char lon[20];
    char lat[20];
    char ele[20];
    dtostrf(longitude, 1, 6, lon);
    dtostrf(latitude, 1, 6, lat);
    dtostrf(elevation, 1, 3, ele);

    sprintf(buffer, "\t\t\t<trkpt lat=\"%s\" lon=\"%s\">\n\t\t\t\t<ele>%s</ele>\n\t\t\t\t<time>20%.2d-%.2d-%.2dT%.2d:%.2d:%.2dZ</time>\n\t\t\t</trkpt>\n\n\t\t</trkseg>\n\t</trk>\n</gpx>", lat, lon, ele, year%100, month%100, day%100, hour%100, minute%100, second%100);
    return true;
}