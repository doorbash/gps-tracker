#ifndef GNSS
#define GNSS

#include "config.h"
#include <Arduino.h>

class Gnss {
  public:
    static bool Gnss::parseGnsInf(char *gnsinf, char *data);
};

#endif
