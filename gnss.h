#ifndef GNSS
#define GNSS

#include <Arduino.h>

class Gnss {
  public:
    static char* parseGnsInf(char *gnsinf);
};

#endif
