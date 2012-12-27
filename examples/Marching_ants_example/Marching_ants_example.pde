/*

  Marching_ants_example.pde - example using i2c_dio_pcf8575c library
  
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


/*

LEDs will illuminate in a 4-LED marching ant pattern that wraps.
Direction is reversed by pulling any of P8..P15 pins low.

Wire P0..P7 to LEDs as follows:
PORT  RES     LED     PWR
P0 ---/\/--- -LED+ ---[+5]
P1 ---/\/--- -LED+ ---[+5]
...
P7 ---/\/--- -LED+ ---[+5]

Wire P8..P15 to pullup resistor as follows:
      +5
       >
       <
       |
P08 ---+---

P09 ---+---
...
P15 ---+---

*/


#include <Wire.h>
#include <i2c_dio_pcf8575c.h>


// instantiate i2c_dio_pcf8575c objects
i2c_dio_pcf8575c device[8];


void setup()
{
  // initialize serial interface
  Serial.begin(19200);
  
  // initialize device ID, i2c interface for each object
  for (uint8_t i = 0; i < 8; i++)
  {
    device[i].begin(i);
  }
}


void loop()
{
  uint8_t s;
  static uint8_t dir, i, j;
  
  // perform bit shift based on direction flag
  if (dir)
  {
    j >>= 1;
    switch (j)
    {
      // start
      case 0b00000000:
        j = 0b11110000;
        break;
        
      // wrap
      case 0b00000111:
      case 0b01000011:
      case 0b01100001:
      case 0b01110000:
        j |= 0b10000000;
        break;
    }
  }
  else
  {
    j <<= 1;
    switch (j)
    {
      // start
      case 0b00000000:
        j = 0b00001111;
        break;
        
      // wrap
      case 0b11100000:
      case 0b11000010:
      case 0b10000110:
      case 0b00001110:
        j |= 0b00000001;
        break;
    }
  }
  
  // display LED bits on serial console
  Serial.print("j=");
  Serial.println(j, BIN);
  
  // loop to write/read each device
  for (i = 0; i < 8; i++)
  {
    // display device information on serial console
    Serial.print("Device ");
    Serial.print(device[i].id(), DEC);
    Serial.print(": ");
    
    // attempt to write 16-bit word
    s = device[i].digitalWrite(word(0, j));
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
    s = device[i].digitalRead();
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
      Serial.print(device[i].data, HEX);
      Serial.println(".");
      
      // set direction bit based on pins P8..P15
      dir = highByte(device[0].data);
    }
  }
  
  Serial.println("- - - - - - - - - - - - - - - - - - - - - - -");
  delay(100);
}

