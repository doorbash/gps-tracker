#include "config.h"
#include <LowPower.h>
#include "serial_handler.h"
#include "gnss.h"

SerialHandler serial;

void zzz() {
  SerialHandler::debug("Good Night!");
#ifdef DEBUG_MODE
  delay(1000);
#endif
  for (int i = 0; i < 2; i++) {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}

void setup() {
  serial.init();

  if (SERIAL_TX_BUFFER_SIZE != 256 || SERIAL_RX_BUFFER_SIZE != 256) {
    while (true) {
      SerialHandler::debug("please set hardware serial rx/tx buffer size to 256");
      delay(1000);
    }
  }
#ifdef SOFTWARE_SERIAL
  if (_SS_MAX_RX_BUFF != 256) {
    while (true) {
      SerialHandler::debug("please set software serial rx buffer size to 256");
      delay(1000);
    }
  }
#endif

  ADCSRA = 0;

  delay(1000);
}

void loop() {
  SerialHandler::debug("Hello There!");

  // setup serial
  serial.command("AT");
  delay(500);

  serial.command("AT+IPR=%d", BAUD_RATE_SERIAL);
  delay(500);

  // get location
  serial.command("AT+CGNSPWR=1");
  delay(500);
  serial.command("AT+CGNSSEQ=GGA");
  delay(500);

  char data[150];
  int i = 0;
  for (; i < 5; i++) {
    serial.command("AT+CGNSINF");
    delay(1000);
    bool result = Gnss::parseGnsInf(serial.gnsinf, data);
    serial.gnsinf[0] = 0;
    if (result) break;
    SerialHandler::debug("gps data is trash...");
    delay(6000);
  }

  if (i == 5) {
    zzz();
    return;
  }

  // setup gprs
  serial.command("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  delay(500);
  serial.command("AT+SAPBR=3,1,\"APN\",\"mcinet\"");
  delay(500);
  serial.command("AT+SAPBR=1,1");
  delay(1000);
  serial.command("AT+SAPBR=2,1");
  delay(1000);

  // send location to server
  serial.command("AT+HTTPINIT");
  delay(500);
#ifdef HTTPSSL
  serial.command("AT+HTTPSSL=1");
  delay(500);
#endif
  serial.command("AT+HTTPPARA=\"CID\",1");
  delay(500);
  serial.command(
    "AT+HTTPPARA=\"URL\",\"%s\"", BACKEND_URL);
  delay(500);
  serial.command(
    "AT+HTTPPARA=\"CONTENT\",\"application/x-www-form-urlencoded\"");
  delay(500);

  serial.command("AT+HTTPDATA=%d,3000", strlen(data));
  delay(500);
  serial.command(data);
  delay(3000);

  serial.command("AT+HTTPACTION=1");
  delay(10000);

  serial.command("AT+HTTPREAD");
  delay(500);
  serial.command("AT+HTTPTERM");
  delay(500);

  // disconnect gprs
  serial.command("AT+SAPBR=0,1");
  delay(500);

  zzz();
}
