#ifndef GUI_MAN_H
#define GUI_MAN_H

namespace GUI {
  /*
    initialize display
  */
  bool init();

  /*
    displays custom splash screen
  */
  void splash();

  /*
    displays GUI background
  */
  void base();

  /*
    displays current date
  */
  void date(int year, int month, int day);

  /*
    displays current time
  */
  void time(int hour, int minute);

  /*
    displays the current amount of used satellites
  */
  void satCount(int count);

  /*
    displays a screen with an info message
  */
  void infoMessage(const char* message);

  /*
    displays a screen with an error message
  */
  void errorMessage(const char* message);

  /*
    displays starting screen with button prompt
  */
  void startScreen();

  /*
    displays screen with info about the current tracking session
  */
  void trackingScreen(int secondsSinceStart, float latitude, float longitude, int metersTraveled);

  /*
    displays screen with stats ebout ended session
  */
  void endScreen(int secondsSinceStart, int metersTraveled);
}

#endif //GUI_MAN_H  