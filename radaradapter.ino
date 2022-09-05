#include <Wire.h>
#include "ld303-protocol.h"

//Standard MaxsonarI2CXL address
#define I2C_SLAVE_ADDR  0x70  


static LD303Protocol protocol;
static char cmdline[128];

//number of readings to average
const int numReadings = 10;




int distances = 0;
unsigned char CS;
uint8_t Index;
byte received;
uint8_t buf[32];
uint8_t data[16];

void readradar(){     
     // process incoming data from radar
     while (Serial.available()) {
        uint8_t c = Serial.read();
        int len = protocol.get_data(buf);
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
        distances = 0.1 * dist;
            }
        }
    }
     

//look for i2c read read request
   void receiveEvent(int howMany) {
      while (Wire.available()) { // loop through all but the last
        {         
      received = Wire.read(); 
      if (received == 0x51)
      {

    }
  }
}
}
//send results over i2c
void requestEvent() 
{  
Wire.write (highByte(distances));
Wire.write (lowByte(distances));
}

void setup() {
 Serial.begin(115200);
 Wire.begin(I2C_SLAVE_ADDR);
 Wire.onReceive(receiveEvent); // register event
 Wire.onRequest(requestEvent);
}
void loop() {
  readradar();
}
