#ifndef GUI_H
#define GUI_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

namespace GUI {
  extern Adafruit_SH1106G *display;
  void init();
  void redraw();
}

#endif //GUI_H  