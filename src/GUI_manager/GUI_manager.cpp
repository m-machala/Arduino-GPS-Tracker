#include "GUI_manager.hpp"
#include "../bitmaps/bitmaps.hpp"

Adafruit_SH1106G *GUI::display = new Adafruit_SH1106G(128, 64, &Wire, -1);

void GUI::init() {
  display->begin(0x3c, true); // i2c address
  display->setTextSize(1);
  display->setTextColor(SH110X_WHITE);
  redraw();
}

void GUI::redraw() {
  display->clearDisplay();
  display->drawBitmap(117, 53, BM::Satellite, BM_Satellite_W, BM_Satellite_H, 1);
  display->drawRect(0, 0, 128, 16, SH110X_WHITE);
  display->drawLine(43, 0, 43, 15, SH110X_WHITE);
  display->drawRect(0, 0, 128, 64, SH110X_WHITE);
  display->display();
}