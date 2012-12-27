/*

  PCF8575C_example.pde - example using i2c_dio_pcf8575c library
  
  This file is part of i2c_dio_pcf8575c.
  
  i2c_dio_pcf8575c is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  i2c_dio_pcf8575c is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with i2c_dio_pcf8575c.  If not, see <http://www.gnu.org/licenses/>.
  
  Written by Doc Walker (Rx)
  Copyright © 2009-2012 Doc Walker <4-20ma at wvfans dot net>
  
*/


#include <Wire.h>
#include <i2c_dio_pcf8575c.h>


// instantiate i2c_dio_pcf8575c object
i2c_dio_pcf8575c dio;


void setup()
{
  // initialize serial interface
  Serial.begin(19200);
  
  // initialize i2c interface; defaults to device ID 0
  dio.begin();
}


void loop()
{
  // byte to store status of read/write operation
  uint8_t s;
  
  Serial.print("Device 0: ");
  
  // attempt to write 16-bit word
  // - bitwise inversion is enabled by default so a 1 is actually written as a 0
  // - if bit = 0, pin functions as input or an output that is off
  // - if bit = 1, pin functions as an output that is on
  // - set pins P15..P8 to inputs (high byte of word = 0x00)
  // - set pins P7..P0 to outputs (low byte of word = random())
  // - successful write returns 0
  s = dio.digitalWrite(word(0x00, random(0x100)));
  if (s)
  {
    // display error information on serial console
    Serial.print("write error 0x");
    Serial.print(s, HEX);
    Serial.print("; ");
  }
  else
  {
    // display success information on serial console
    Serial.print("write OK; ");
  }
  
  // attempt to read 16-bit word
  // - successful read returns 0
  s = dio.digitalRead();
  if (s)
  {
    // display error information on serial console
    Serial.print("read error 0x");
    Serial.print(s, HEX);
    Serial.println(".");
  }
  else
  {
    // display success information on serial console
    Serial.print("read OK 0x");
    Serial.print(dio.data, HEX);
    Serial.println(".");
  }
  
  Serial.println("- - - - - - - - - - - - - - - - - - - - - - -");
  delay(1000);
}

