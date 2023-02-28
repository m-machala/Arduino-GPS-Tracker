#include "display_manager.hpp"

Adafruit_SH1106G *DISP_MAN::display = new Adafruit_SH1106G(128, 64, &Wire, -1);

bool DISP_MAN::init() {
    bool output = display->begin(0x3c, true); // i2c address
    display->setTextSize(1);
    display->setTextColor(SH110X_WHITE);
    display->display(); // shows default splash screen
    return output;
}

void DISP_MAN::draw() {
    display->display();
}

void DISP_MAN::clearScreen() {
    display->clearDisplay();
}

void DISP_MAN::clearRect(int x, int y, int w, int h) {
    if(x < 0) x = 0;
    if(x >= X_MAX) x = X_MAX - 1;
    if(y < 0) y = 0;
    if(y >= Y_MAX) y = Y_MAX - 1;

    display->fillRect(x, y, w, h, SH110X_BLACK); // fills area with black color
}
    
void DISP_MAN::printText(const char* text, int x, int y) {
    if(x < 0) x = 0;
    if(x >= X_MAX) x = X_MAX - 1;
    if(y < 0) y = 0;
    if(y >= Y_MAX) y = Y_MAX - 1;

    display->setCursor(x, y);

    for(int i = 0; i < strlen(text); i++) {
        if(text[i] == '\n') {
            y += 8;
            display->setCursor(x, y);
            continue;
        }
        display->print(text[i]);
    }
}

void DISP_MAN::drawLine(int x1, int y1, int x2, int y2) {
    if(x1 < 0) x1 = 0;
    if(x1 >= X_MAX) x1 = X_MAX - 1;
    if(y1 < 0) y1 = 0;
    if(y1 >= Y_MAX) y1 = Y_MAX - 1;
    if(x2 < 0) x2 = 0;
    if(x2 >= X_MAX) x2 = X_MAX - 1;
    if(y2 < 0) y2 = 0;
    if(y2 >= Y_MAX) y2 = Y_MAX - 1;

    display->drawLine(x1, y1, x2, y2, SH110X_WHITE);
}

void DISP_MAN::drawRect(int x, int y, int w, int h) {
    if(x < 0) x = 0;
    if(x >= X_MAX) x = X_MAX - 1;
    if(y < 0) y = 0;
    if(y >= Y_MAX) y = Y_MAX - 1;

    display->drawRect(x, y, w, h, SH110X_WHITE);
}

void DISP_MAN::drawBM(int x, int y, int w, int h, const uint8_t* bitmap) {
    display->drawBitmap(x, y, bitmap, w, h, SH110X_WHITE);
}