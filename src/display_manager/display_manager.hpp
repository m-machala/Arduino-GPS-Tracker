#ifndef DISP_MAN_H
#define DISP_MAN_H

#define X_MAX (128)
#define Y_MAX (64)

#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <stdint.h>

namespace DISP_MAN {
    static Adafruit_SH1106G display;

    /*
        initialize display component
    */
    bool init();

    /*
        clears all pixels of screen
    */
    void clearScreen();

    /*
        clears set area of screen based on rect defined by coordinates
    */
    void clearRect(int x, int y, int w, int h);
    
    /*
        prints text at specified coordinates
    */
    void printText(const char* text, int x, int y);

    /*
        draws a line defined by coordinates
    */
    void drawLine(int x1, int y1, int x2, int y2);

    /*
        draws rect defined by coordinates
    */
    void drawRect(int x, int y, int w, int h);

    /*
        draws bitmap
    */
    void drawBM(int x, int y, int w, int h, uint8_t* bitmap);
}

#endif //DISP_MAN_H