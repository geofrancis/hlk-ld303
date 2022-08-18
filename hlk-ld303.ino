#include "Arduino.h"
#include <SoftwareSerial.h>

#include "ld303-protocol.h"

#define PIN_TX  D2
#define PIN_RX  D3

#define printf Serial.printf

static LD303Protocol protocol;
static SoftwareSerial radar(PIN_RX, PIN_TX);
static char cmdline[128];
static bool debug = false;

static void printhex(const char *prefix, const uint8_t * buf, size_t len)


void setup(void)
{
    Serial.begin(115200);
    radar.begin(115200);
}

void loop(void)
{
     // process incoming data from radar
    while (radar.available()) {
        uint8_t c = radar.read();
        if (debug) {
            printf(" %02X", c);
        }

        // run receive state machine
        bool done = protocol.process_rx(c);
        if (done) {
            int len = protocol.get_data(buf);
            printhex("<", buf, len);
            uint8_t cmd = buf[0];
            switch (cmd) {
            case 0xD3:
                int dist = (buf[1] << 8) + buf[2];
                int pres = buf[4];
                int k = (buf[5] << 8) + buf[6];
                int micro = buf[7];
                int off = buf[8];
                printf("distance=%3d,present=%d,strength=%5d,micro=%d,off=%d\n", dist, pres, k, micro, off);
                break;
            }
        }
    }
}

