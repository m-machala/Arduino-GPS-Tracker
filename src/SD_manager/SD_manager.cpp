#include "SD_manager.h"

static File currentFile;

bool SD_MAN::init() {
    // pin connected to CS
    return SD.begin(53);
}

bool SD_MAN::openFileWrite(char* fileName) {
    currentFile = SD.open(fileName, FILE_WRITE);
    if(currentFile) return true;
    return false;
}

void SD_MAN::fileWrite(char* text) {
    currentFile.println(text);
}

void SD_MAN::closeFile() {
    currentFile.close();
}

void SD_MAN::seek(uint32_t bytes) {
    currentFile.seek(bytes);
}

void SD_MAN::seekBack(uint32_t bytes) {
    currentFile.seek(currentFile.size() - bytes);
}