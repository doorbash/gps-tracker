#ifndef SERIAL_HANDLER
#define SERIAL_HANDLER

#include "config.h"
#include <Arduino.h>
#if defined(SOFTWARE_SERIAL)
#include <SoftwareSerial.h>
#endif

class SerialHandler {
  private:
    int baudRate;
    Stream *module;
#if defined(SOFTWARE_SERIAL)
    SoftwareSerial ss {SS_RX_PIN, SS_TX_PIN};
#endif
    char buffer[MAX_BUFFER_SIZE];
    int bufferIndex;

  public:
    char gnsinf[200];

    SerialHandler(int br);
    void init();
    void send(char *text);
    void receive();
    void command(char *text);
    void command(const char *format, ...);
    static void debug(char *text);
    static void debug(const char *format, ...);
};

#endif
