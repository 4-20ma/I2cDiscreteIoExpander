## Overview
This is an Arduino library for the Texas Instruments PCF8575C 16-bit I2C I/O expander.

## Features
The PCF8575C provides general-purpose remote I/O expansion for most microcontroller families via the I2C interface serial clock (SCL) and serial data (SDA).

The device features a 16-bit quasi-bidirectional input/output (I/O) port (P07..P00, P17..P10), including latched outputs with high-current drive capability for directly driving LEDs. Each quasi-bidirectional I/O can be used as an input or output without the use of a data-direction control signal. At power on, the I/Os are in 3-state mode. The strong pullup to VCC allows fast-rising edges into heavily loaded outputs. This device turns on when an output is written high and is switched off by the negative edge of SCL. The I/Os should be high before being used as inputs. After power on, as all the I/Os are set to 3-state, all of them can be used as inputs. Any change in setting of the I/Os as either inputs or outputs can be done with the write mode. If a high is applied externally to an I/O that has been written earlier to low, a large current (IOL) flows to GND.

The fixed I2C address of the PCF8575C is the same as the PCF8575, PCF8574, PCA9535, and PCA9555, allowing up to eight of these devices, in any combination, to share the same I2C bus or SMBus.

## Hardware
This library has been tested with an Arduino [Duemilanove](http://www.arduino.cc/en/Main/ArduinoBoardDuemilanove) and a Texas Instruments [PCF8575C](http://www.ti.com/product/pcf8575c) remote I/O expander.

## Installation
Determine the location of your sketchbook by selecting _File > Preferences_ from within the Arduino IDE. If you don't already have a _libraries_ folder within your sketchbook, create one and unzip the archive there. See [this](http://arduino.cc/blog/?p=313) for more information.

Note: Arduino 1.0 or later is required.

## Support
Full [source code documentation](http://4-20ma.github.com/I2cIoExpander/) is available. Please report any bugs on the [Issue Tracker](/4-20ma/I2cIoExpander/issues).

## Questions/Feedback
I can be contacted at 4-20ma at wvfans dot net.

## Schematic
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
The library contains sketches that demonstrates use of the I2cIoExpander library. You can find these in the [examples](/4-20ma/I2cIoExpander/tree/master/examples/) folder.

```c++
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
```
