#include "serial_handler.h"

#include <Arduino.h>

SerialHandler::SerialHandler(int baudRate) {
  this->baudRate = baudRate;
}

void SerialHandler::init() {
#ifdef SOFTWARE_SERIAL
#ifdef DEBUG_MODE
  Serial.begin(baudRate);
#endif
  module = &ss;
  ss.begin(baudRate);
#else
  module = &Serial;
  Serial.begin(baudRate);
#endif
}

void SerialHandler::send(char *text) {
  module->println(text);
#ifdef DEBUG_MODE
#ifdef SOFTWARE_SERIAL
  Serial.println(text);
#endif
#endif
}

void SerialHandler::receive() {
  bufferIndex = 0;
  buffer[0] = 0;
  while (module->available()) {
    char c = module->read();
    if (c == '\r') continue;
    if (c == '\n' || bufferIndex >= MAX_BUFFER_SIZE - 1) {
      buffer[bufferIndex] = 0;
      bufferIndex = 0;
      if (strstr(buffer, "+CGNSINF") == buffer) {
        strcpy(gnsinf, buffer);
      }
#ifdef DEBUG_MODE
      Serial.print("> ");
      Serial.println(buffer);
#endif
      continue;
    }
    buffer[bufferIndex++] = c;
  }
}

void SerialHandler::command(char *text) {
  while (module->available())
    module->read();
  send(text);
  unsigned long current_time = millis();
  while (module->available() == 0 && millis() - current_time < 3000);
  delay(1000);
  receive();
}

void SerialHandler::command(const char *format, ...) {
  va_list args;
  char buf[100];
  va_start(args, format);
  vsnprintf(buf, sizeof(buf), format, args);
  va_end(args);
  command(buf);
}

static void SerialHandler::debug(char *text) {
#ifdef DEBUG_MODE
  Serial.println(text);
#endif
}

static void SerialHandler::debug(const char *format, ...) {
  va_list args;
  char buf[100];
  va_start(args, format);
  vsnprintf(buf, sizeof(buf), format, args);
  va_end(args);
  debug(buf);
}
