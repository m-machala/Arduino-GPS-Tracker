#include "SD_manager.hpp"

bool SD_MAN::init() {
    // pin connected to CS
    return SD.begin(53);
}

bool SD_MAN::openFileWrite(const char* fileName) {
    currentFile = SD.open(fileName, O_WRITE | O_CREAT | O_TRUNC);
    if(currentFile) return true;
    return false;
}

void SD_MAN::fileWrite(const char* text) {
    currentFile.println(text);
}

void SD_MAN::fileFlush() {
    currentFile.flush();
}

void SD_MAN::fileClose() {
    currentFile.close();
}

void SD_MAN::seek(uint32_t bytes) {
    currentFile.seek(bytes);
}

void SD_MAN::seekBack(uint32_t bytes) {
    currentFile.seek(currentFile.size() - (bytes + 2));
}
