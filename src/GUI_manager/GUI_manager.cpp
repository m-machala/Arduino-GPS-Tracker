#include "GUI_manager.hpp"
#include "../display_manager/display_manager.hpp"
#include "../bitmaps/bitmaps.hpp"

bool GUI_MAN::init() {
    return DISP_MAN::init();
}

void GUI_MAN::splash() {
    DISP_MAN::clearScreen();
    DISP_MAN::drawRect(0, 0, X_MAX, Y_MAX);
    DISP_MAN::drawBM(44, 22, BM_SPLASH_W, BM_SPLASH_H, BM::splash);
    DISP_MAN::printText("By: Martin Machala", 10, Y_MAX - 10);
    DISP_MAN::draw();
}

void GUI_MAN::base() {
    DISP_MAN::clearScreen();
    DISP_MAN::drawRect(0, 0, X_MAX, 13);
    DISP_MAN::drawRect(0, 0, X_MAX, Y_MAX);
    DISP_MAN::drawRect(34, 0, 65, 13);
    DISP_MAN::draw();
}

void clearMainScreen() {
    DISP_MAN::clearRect(1, 13, X_MAX - 2, Y_MAX - 14);
}

void GUI_MAN::date(int year, int month, int day) {
    DISP_MAN::clearRect(35, 1, 62, 11);
    year %= 100;
    month %= 100;
    day %= 100;
    char date[15];
    sprintf(date, "20%.2d-%.2d-%.2d", year, month, day);
    DISP_MAN::printText(date, 37, 3);
    DISP_MAN::draw();
}

void GUI_MAN::time(int hour, int minute) {
    DISP_MAN::clearRect(1, 1, 33, 11);
    hour %= 100;
    minute %= 100;
    char time[10];
    sprintf(time, "%.2d:%.2d", hour, minute);
    DISP_MAN::printText(time, 3, 3);
    DISP_MAN::draw();
}

void GUI_MAN::satCount(int count) {
    DISP_MAN::clearRect(99, 1, 28, 11);
    DISP_MAN::drawBM(117, 2, BM_SATELLITE_W, BM_SATELLITE_H, BM::satellite);
    char sats[6];
    sprintf(sats, "%.2d", count % 100);
    DISP_MAN::printText(sats, 102, 3);
    DISP_MAN::draw();
}

void GUI_MAN::infoMessage(const char* message) {
    clearMainScreen();
    DISP_MAN::drawBM(3, 15, BM_QUESTION_W, BM_QUESTION_H, BM::question);
    DISP_MAN::drawBM(3, Y_MAX - 12, BM_QUESTION_W, BM_QUESTION_H, BM::question);
    DISP_MAN::drawBM(X_MAX - 9, 15, BM_QUESTION_W, BM_QUESTION_H, BM::question);
    DISP_MAN::drawBM(X_MAX - 9, Y_MAX - 12, BM_QUESTION_W, BM_QUESTION_H, BM::question);
    DISP_MAN::printText(message, 11, 15);
    DISP_MAN::draw();
}

void GUI_MAN::errorMessage(const char* message) {
    clearMainScreen();
    DISP_MAN::drawBM(3, 15, BM_EXCLAMATION_W, BM_EXCLAMATION_H, BM::exclamation);
    DISP_MAN::drawBM(3, Y_MAX - 12, BM_EXCLAMATION_W, BM_EXCLAMATION_H, BM::exclamation);
    DISP_MAN::drawBM(X_MAX - 9, 15, BM_EXCLAMATION_W, BM_EXCLAMATION_H, BM::exclamation);
    DISP_MAN::drawBM(X_MAX - 9, Y_MAX - 12, BM_EXCLAMATION_W, BM_EXCLAMATION_H, BM::exclamation);
    DISP_MAN::printText(message, 11, 15);
    DISP_MAN::draw();
}

void GUI_MAN::startScreen() {
    clearMainScreen();
    DISP_MAN::printText("GPS tracker\nComponents started\nsuccessfully!\n\nPress 1 to start\ntracking", 3, 15);
    DISP_MAN::draw();
}

void GUI_MAN::trackingScreen(int hours, int minutes, float latitude, float longitude, int kmTraveled, bool paused) {
    clearMainScreen();
    char lat[20];
    char lon[20];
    dtostrf(longitude, 1, 4, lon);
    dtostrf(latitude, 1, 4, lat);

    char buffer[150];
    sprintf(buffer, "Tracking in progress\nDuration: %d:%.2d\nDistance: %d km\n%sN %sE", hours, minutes % 100, kmTraveled, lat, lon);
    DISP_MAN::printText(buffer, 3, 15);
    if(!paused) DISP_MAN::printText("Press 1 to pause", 3, 55);
    else DISP_MAN::printText("Press 1 to unpause\nPress 2 to stop", 3, 47);

    DISP_MAN::draw();
}

void GUI_MAN::endScreen(int hours, int minutes, int kmTraveled) {
    clearMainScreen();
    char buffer[150];
    sprintf(buffer, "Tracking finished!\nDuration: %d:%.2d\nDistance: %d km\n\nPress 1 to start\ntracking a new route", hours, minutes % 100, kmTraveled);
    DISP_MAN::printText(buffer, 3, 15);
    DISP_MAN::draw();
}