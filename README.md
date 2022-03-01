### Config:

Edit `<arduino ide directory>/hardware/arduino/avr/cores/arduino/HardwareSerial.h`

Change:
```
#define SERIAL_TX_BUFFER_SIZE 64
#define SERIAL_RX_BUFFER_SIZE 64
```

To:
```
#define SERIAL_TX_BUFFER_SIZE 256
#define SERIAL_RX_BUFFER_SIZE 256
```

Edit `<arduino ide directory>/hardware/arduino/avr/libraries/SoftwareSerial/src/SoftwareSerial.h`:

Change:
```
#define _SS_MAX_RX_BUFF 64
```

To:
```
#define _SS_MAX_RX_BUFF 256
```

Create `config.h`:
```
#define SOFTWARE_SERIAL
#define DEBUG_MODE
#define MAX_BUFFER_SIZE 200
#define BAUD_RATE_SERIAL 9600
#define SS_RX_PIN 7
#define SS_TX_PIN 8
#define BACKEND_URL "http://your.domain.com/gps-tracker/"
// #define HTTPSSL
#define DEVICE_ID "00000000000000000000"
```

### Todo:
- [x] Add device id
- [ ] Add better sleep mode (to make it more energy efficient)
