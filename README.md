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
#define BAUD_RATE_SERIAL 9600
#define SS_RX_PIN 7
#define SS_TX_PIN 8
#define BACKEND_URL "http://****************/gps-tracker/"
#define HTTPSSL false
```

### Todo:
- [ ] Add better sleep mode (to make it more energy efficient)
- [ ] Add device hash id
