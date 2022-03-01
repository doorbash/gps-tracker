#include "gnss.h"
// #include "serial_handler.h"

static bool Gnss::parseGnsInf(char *gnsinf, char *data) {
  // SerialHandler::debug("parseGnsInf: trying to parse: %s", gnsinf);
  char *b = gnsinf;
  char *temp;
  char *datetime_str = NULL;
  char *latitude_str = NULL;
  char *longitude_str = NULL;
  char *altitude_str = NULL;
  char *hdop_str = NULL;
  char *pdop_str = NULL;
  char *vdop_str = NULL;

  temp = strsep(&b, ",");
  if (temp == NULL || *temp == 0) {
    return false;
  }
  strsep(&b, ",");  // fix status

  datetime_str = strsep(&b, ",");
  if (datetime_str == NULL || *datetime_str == 0) {
    return false;
  }

  latitude_str = strsep(&b, ",");
  if (latitude_str == NULL || *latitude_str == 0) {
    return false;
  }

  longitude_str = strsep(&b, ",");
  if (longitude_str == NULL || *longitude_str == 0) {
    return NULL;
  }

  altitude_str = strsep(&b, ",");
  if (altitude_str == NULL || *altitude_str == 0) {
    return false;
  }

  strsep(&b, ",");  // speed
  strsep(&b, ",");  // course
  strsep(&b, ",");  // fix mode
  strsep(&b, ",");  // reserved

  hdop_str = strsep(&b, ",");
  if (hdop_str == NULL || *hdop_str == 0) {
    return false;
  }

  pdop_str = strsep(&b, ",");
  if (pdop_str == NULL || *pdop_str == 0) {
    return false;
  }

  vdop_str = strsep(&b, ",");
  if (vdop_str == NULL || *vdop_str == 0) {
    return false;
  }

  sprintf(
    data,
    "did=%s&dt=%s&lat=%s&lng=%s&alt=%s&hdop=%s&pdop=%s&vdop=%s",
    DEVICE_ID,
    datetime_str,
    latitude_str,
    longitude_str,
    altitude_str,
    hdop_str,
    pdop_str,
    vdop_str);
}
