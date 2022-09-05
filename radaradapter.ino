#include <Wire.h>
#include "ld303-protocol.h"

//Standard MaxsonarI2CXL address
#define I2C_SLAVE_ADDR  0x70  


static LD303Protocol protocol;
static char cmdline[128];

//number of readings to average
const int numReadings = 10;

static void printhex(const char *prefix, const uint8_t * buf, size_t len)


int readings[numReadings]; 
int readIndex = 0; 
int total = 0;  
int average = 0; 


void readradar(){     
     // process incoming data from radar
    while (Serial.available()) {
        uint8_t c = radar.read();
          int len = protocol.get_data(buf);
      uint8_t cmd = buf[0];
         int dist = (buf[1] << 8) + buf[2];
         int pres = buf[4];
          n int k = (buf[5] << 8) + buf[6];
        int micro = buf[7];
          int off = buf[8];
        distances = 0.1 * dist;
            }
        }
    }
}

         
// Smoothing
{
// subtract the last reading:       
        total = total - readings[readIndex];
        
// read from the sensor:    
         readings[readIndex] = distances ;
         
// add the reading to the total:
         total = total + readings[readIndex];
         
// advance to the next position in the array:
        readIndex = readIndex + 1;
        
// if we're at the end of the array...
    if (readIndex >= numReadings) 
    // ...wrap around to the beginning:
    {readIndex = 0;
    }
// calculate the average:
      average = total / numReadings;
} 
//ratio for speed of sound in air vs water 4.314 for water, 1.0 for use in air
       distance = average * 4.314 ;    
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
Wire.write (highByte(distance));
Wire.write (lowByte(distance));
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
