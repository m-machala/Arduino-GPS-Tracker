#ifndef DISP_MAN_H
#define DISP_MAN_H

#define X_MAX (128)
#define Y_MAX (64)

#include <stdint.h>

namespace DISP_MAN {
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
    void clearRect(int x1, int y1, int x2, int y2);
    
    /*
        prints text at specified coordinates
    */
    void printText(const char* text, int x, int y);

    /*
        draws rect defined by coordinates
    */
    void drawRect(int x1, int y1, int x2, int y2);

    /*
        draws bitmap
    */
    void drawBM(uint8_t* bitmap, int w, int h, int x, int y);
}

#endif //DISP_MAN_H