#include <Arduino.h>
#include "GUI_manager/GUI_manager.hpp"
#include "GPS_manager/GPS_manager.hpp"

const uint8_t bufferSize = 15;
char buffer[bufferSize];

void setup()   {
  buffer[bufferSize - 1] = '\0';
  Serial.begin(115200);
  GUI::init();
  GPS_MAN::init();
}


void loop() {
  while(!GPS_MAN::update()) {
    ;
  }
  
  GUI::redraw();
  GUI::display->setCursor(35, 30);
  GPS_MAN::getTimeReadable(buffer, bufferSize);
  GUI::display->print(buffer);
  GUI::display->setCursor(35, 20);
  GUI::display->print(GPS_MAN::getSats(), 10);
  GUI::display->setCursor(35, 40);
  GUI::display->print(GPS_MAN::getLat());
  GUI::display->setCursor(35, 50);
  GUI::display->print(GPS_MAN::getLon());
  GUI::display->display();

  if(GPS_MAN::fix()) {
    Serial.print("Latitude: ");
  Serial.print(GPS_MAN::getLat());
  Serial.print(GPS_MAN::GPS.lat);
  Serial.print("  Longitude: ");
  Serial.print(GPS_MAN::getLon());
  Serial.print(GPS_MAN::GPS.lon);
  Serial.print("  Satelites: ");
  Serial.print(GPS_MAN::getSats());
  Serial.println("\n---------");
  }
  

  delay(750);
}