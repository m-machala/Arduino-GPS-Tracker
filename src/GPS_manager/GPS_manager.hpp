#ifndef GPS_MAN_H
#define GPS_MAN_H

#define NO_SW_SERIAL
#include <Arduino.h>
#include <Adafruit_GPS.h>

namespace GPS_MAN {
  /*
    GPS pins - Mega2560 pins
    TX - TX1 18
    RX - RX1 19
  */ 
  static Adafruit_GPS GPS(&Serial1);

  /*
    initialize GPS
  */
  void init();

   /*
     update GPS data
     true - new data available
     false - no new data available
   */
   bool update();

   /*
     get number of satellites the module is communicating with
   */
   int getSats();

   /*
     get longitude of GPS
   */
   float getLon();

   /*
     get latitude of GPS
   */
   float getLat();

   /*
     get altitude of GPS
   */
   float getAlt();

   /*
     get time in a format ready to be displayed
     HH:MM
   */
   char* getTimeReadable();

   /*
     get date in a format ready to be displayed
     DD.MM.YY
   */
   char* getDateReadable();
}

#endif //GPS_H  