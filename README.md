# I2cDiscreteIoExpander
[![GitHub release](https://img.shields.io/github/release/4-20ma/I2cDiscreteIoExpander.svg?maxAge=3600)][GitHub release]
[![Travis](https://img.shields.io/travis/4-20ma/I2cDiscreteIoExpander.svg?maxAge=3600)][Travis]
[![license](https://img.shields.io/github/license/4-20ma/I2cDiscreteIoExpander.svg?maxAge=3600)][license]
[![code of conduct](https://img.shields.io/badge/%E2%9D%A4-code%20of%20conduct-blue.svg?maxAge=3600)][code of conduct]

[GitHub release]:   https://github.com/4-20ma/I2cDiscreteIoExpander
[Travis]:           https://travis-ci.org/4-20ma/I2cDiscreteIoExpander
[license]:          LICENSE
[code of conduct]:  CODE_OF_CONDUCT.md


## Overview
This is an Arduino library for the Texas Instruments PCF8575C 16-bit I<sup>2</sup>C I/O expander.


## Features
The PCF8575C provides general-purpose remote I/O expansion for most microcontroller families via the I<sup>2</sup>C interface serial clock (SCL) and serial data (SDA).

The device features a 16-bit quasi-bidirectional input/output (I/O) port (P07..P00, P17..P10), including latched outputs with high-current drive capability for directly driving LEDs. Each quasi-bidirectional I/O can be used as an input or output without the use of a data-direction control signal. At power on, the I/Os are in 3-state mode. The strong pullup to VCC allows fast-rising edges into heavily loaded outputs. This device turns on when an output is written high and is switched off by the negative edge of SCL. The I/Os should be high before being used as inputs. After power on, as all the I/Os are set to 3-state, all of them can be used as inputs. Any change in setting of the I/Os as either inputs or outputs can be done with the write mode. If a high is applied externally to an I/O that has been written earlier to low, a large current (IOL) flows to GND.

The fixed I<sup>2</sup>C address of the PCF8575C (0x20) is the same as the PCF8575, PCF8574, PCA9535, and PCA9555, allowing up to eight of these devices, in any combination, to share the same I<sup>2</sup>C bus or SMBus.


## Installation

#### Library Manager
Install the library into your Arduino IDE using the Library Manager (available from IDE version 1.6.2). Open the IDE and click Sketch > Include Library > Manage Libraries&hellip;

Scroll or search for `I2cDiscreteIoExpander`, then select the version of the library you want to install. Quit/re-launch the IDE to refresh the list; new versions are automatically added to the list, once released on GitHub.

Refer to Arduino Tutorials > Libraries [Using the Library Manager](https://www.arduino.cc/en/Guide/Libraries#toc3).

#### Zip Library
Refer to Arduino Tutorials > Libraries [Importing a .zip Library](https://www.arduino.cc/en/Guide/Libraries#toc4).

#### Manual
Refer to Arduino Tutorials > Libraries [Manual Installation](https://www.arduino.cc/en/Guide/Libraries#toc5).


## Schematic
This library has been tested with an Arduino [Duemilanove](http://www.arduino.cc/en/Main/ArduinoBoardDuemilanove) and a Texas Instruments [PCF8575C](http://www.ti.com/product/pcf8575c) remote I/O expander.

Below is a simplified schematic diagram. Refer to the datasheet for specific requirements.

```
                                        Arduino
                                       .--------------------.
                                       |Duemilanove         |
                                       |                    |
         TI PCF8575C        .---------o|5V                  |
        .-------_-------.   |          |                    |
      -o|1 /INT   VCC 24|o--'   o-----o|GND                 |
        |               |       |      |                    |
.------o|2  A1    SDA 23|o------)-----o|A4 SDA              |
|       |               |       |      |                    |
o------o|3  A2    SCL 22|o------)-----o|A5 SCL              |
|       |               |       |      '--------------------'
|     -o|4  P00    A0 21|o------o
|       |               |       |
|     -o|5  P01   P17 20|o-     |
|       |               |       |
|     -o|6  P02   P16 19|o-     |
|       |               |       |
|     -o|7  P03   P15 18|o-     |
|       |               |       |
|     -o|8  P04   P14 17|o-     |
|       |               |       |
|     -o|9  P05   P13 16|o-     |
|       |               |       |
|     -o|10 P06   P12 15|o-     |
|       |               |       |
|     -o|11 P07   P11 14|o-     |
|       |               |       |
o------o|12 GND   P10 13|o-     |
|       '---------------'       |
|                               |
'-------------------------------o
                                |
                                |
                               ===
                               GND
```


## Example
The library contains sketches that demonstrates use of the `I2cDiscreteIoExpander` library. You can find these in the [examples](/examples/) folder.

``` cpp
#include <I2cDiscreteIoExpander.h>


// instantiate I2cDiscreteIoExpander object
I2cDiscreteIoExpander device;


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
```


## Caveats
Conforms to Arduino IDE 1.5 Library Specification v2.1 which requires Arduino IDE >= 1.5.


## Support
Please [submit an issue](https://github.com/4-20ma/I2cDiscreteIoExpander/issues) for all questions, bug reports, and feature requests. Email requests will be politely redirected to the issue tracker so others may contribute to the discussion and requestors get a more timely response.


## License & Authors

- Author:: Doc Walker ([4-20ma@wvfans.net](mailto:4-20ma@wvfans.net))

```
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
```
