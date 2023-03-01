#ifndef POS_LOG_H
#define POS_LOG_H

namespace POS_LOG {
  /*
    initialize logger
  */
  bool init();

  /*
    generates a .gpx file on the SD card and inserts the GPX skeleton into it
  */
  bool startLogging(const char* creator);

  /*
    inserts a trackpoint into the current working .gpx file
  */
  bool addTrackpoint(float latitude, float longitude, float elevation, int year, int month, int day, int hour, int minute, int second);

  /*
    closes current working file, ends logging
  */
  void stopLogging();
}

#endif //POS_LOG_H