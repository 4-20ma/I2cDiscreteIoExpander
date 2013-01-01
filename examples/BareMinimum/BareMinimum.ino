/*

  BareMinimum.ino - example using I2cIoExpander library
  
  This file is part of I2cIoExpander.
  
  I2cIoExpander is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  I2cIoExpander is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with I2cIoExpander.  If not, see <http://www.gnu.org/licenses/>.
  
  Written by Doc Walker (Rx)
  Copyright © 2009-2012 Doc Walker <4-20ma at wvfans dot net>
  
*/


#include <Wire.h>
#include <I2cIoExpander.h>


// instantiate I2cIoExpander object
I2cIoExpander device;


void setup()
{
  // initialize i2c interface
  Wire.begin();
  
  // initialize serial interface
  Serial.begin(19200);
}


void loop()
{
  uint8_t status;
  static uint16_t i;
  
  // display device information on serial console
  Serial.print("Loop ");
  Serial.print(++i, DEC);
  Serial.print(", address ");
  Serial.print(device.getAddress(), DEC);
  Serial.print(", ");
  
  // attempt to write 16-bit word
  status = device.digitalWrite(i);
  if (TWI_SUCCESS == status)
  {
    // display success information on serial console
    Serial.print("write 0x");
    Serial.print(i, HEX);
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
  status = device.digitalRead();
  if (TWI_SUCCESS == status)
  {
    // display success information on serial console
    Serial.print("read 0x");
    Serial.print(device.getPorts(), HEX);
    Serial.println(".");
  }
  else
  {
    // display error information on serial console
    Serial.print("read error ");
    Serial.print(status, DEC);
    Serial.println(".");
  }
  
  delay(1000);
}
