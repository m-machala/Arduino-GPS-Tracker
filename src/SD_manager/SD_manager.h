#ifndef GUI_MAN_H
#define GUI_MAN_H

#include <SPI.h>
#include <SD.h>

/*
    Current file that is being worked with
*/
static File currentFile;

namespace SD_MAN {
    /*
        Initialize SD module
        true - module initialized successfully
        false - error
    */
    bool init();

    /*
        tries to open a file for writing
        true - file opened/created successfully
        false - error
    */
    bool openFileWrite(const char* fileName);

    /*
        appends a new line to the file
    */
    void fileWrite(const char* text);

    /*
        ensures file is written to
    */
    void fileFlush();

    /*
        closes a file
    */
    void closeFile();

    /*
        moves an amount of bytes from the start of a file
    */
    void seek(uint32_t bytes);

    /* 
        moves an amount of bytes from the end of a file
    */
    void seekBack(uint32_t bytes);
}

#endif //GUI_MAN_H