/*

  MultipleDevices.ino - example using I2cDiscreteIoExpander library
  
  This file is part of I2cDiscreteIoExpander.
  
  I2cDiscreteIoExpander is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  I2cDiscreteIoExpander is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with I2cDiscreteIoExpander.  If not, see <http://www.gnu.org/licenses/>.
  
  Written by Doc Walker (Rx)
  Copyright © 2009-2013 Doc Walker <4-20ma at wvfans dot net>
  
*/


#include <Wire.h>
#include <I2cDiscreteIoExpander.h>


// instantiate I2cDiscreteIoExpander objects
// device addresses purposely out of order to illustrate constructor
I2cDiscreteIoExpander device[8] = { 6, 4, 2, 0, 1, 3, 5, 7 };


void setup()
{
  // initialize i2c interface
  Wire.begin();
  
  // initialize serial interface
  Serial.begin(19200);
}


void loop()
{
  uint8_t status, i;
  static uint16_t j;
  
  // loop to write/read each device
  for (i = 0; i < 8; i++)
  {
    // display device information on serial console
    Serial.print("Loop ");
    Serial.print(j, DEC);
    Serial.print(", device[");
    Serial.print(i, DEC);
    Serial.print("], address ");
    Serial.print(device[i].getAddress(), DEC);
    Serial.print(", ");
    
    // attempt to write 16-bit word
    status = device[i].digitalWrite(j);
    if (TWI_SUCCESS == status)
    {
      // display success information on serial console
      Serial.print("write 0x");
      Serial.print(j, HEX);
      Serial.print(", ");
    }
    else
    {
      // display error information on serial console
      Serial.print("write error ");
      Serial.print(status, DEC);
      Serial.print(", ");
    }
    
    // attempt to read 16-bit word
    status = device[i].digitalRead();
    if (TWI_SUCCESS == status)
    {
      // display success information on serial console
      Serial.print("read 0x");
      Serial.print(device[i].getPorts(), HEX);
      Serial.println(".");
    }
    else
    {
      // display error information on serial console
      Serial.print("read error ");
      Serial.print(status, DEC);
      Serial.println(".");
    }
  }
  
  j++;
  Serial.println("- - - - - - - - - - - - - - - - - - - - - - -");
  delay(1000);
}
