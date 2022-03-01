#ifndef GNSS
#define GNSS

#include "config.h"
#include <Arduino.h>

class Gnss {
  public:
    static char* parseGnsInf(char *gnsinf);
};

#endif
