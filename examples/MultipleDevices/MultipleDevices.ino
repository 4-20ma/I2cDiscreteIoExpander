/*

  MultipleDevices.ino - example using I2cDiscreteIoExpander library

  Library:: I2cDiscreteIoExpander
  Author:: Doc Walker <4-20ma@wvfans.net>

  Copyright:: 2009-2016 Doc Walker

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

*/


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
