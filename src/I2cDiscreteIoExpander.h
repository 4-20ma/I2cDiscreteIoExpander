/// \file
/// Arduino library for TI PCF8575C 16-bit I2C I/O expander.
/*

  I2cDiscreteIoExpander.h - Arduino library for TI PCF8575C 16-bit I2C
  I/O expander.

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


/// \mainpage Arduino library for TI PCF8575C 16-bit I2C I/O expander.
/// \version \verbinclude VERSION
/// \date 27 Sep 2016
/// \par Source Code Repository
///   https://github.com/4-20ma/I2cDiscreteIoExpander
/// \par Programming Style Guidelines
///   http://geosoft.no/development/cppstyle.html
/// 
/// \par Features
/// The PCF8575C provides general-purpose remote I/O expansion for most
/// microcontroller families via the I2C interface serial clock (SCL) and
/// serial data (SDA).<br>
/// <br>
/// The device features a 16-bit quasi-bidirectional input/output (I/O) port
/// (P07..P00, P17..P10), including latched outputs with high-current drive
/// capability for directly driving LEDs. Each quasi-bidirectional I/O can
/// be used as an input or output without the use of a data-direction
/// control signal. At power on, the I/Os are in 3-state mode. The strong
/// pullup to VCC allows fast-rising edges into heavily loaded outputs. This
/// device turns on when an output is written high and is switched off by
/// the negative edge of SCL. The I/Os should be high before being used as
/// inputs. After power on, as all the I/Os are set to 3-state, all of them
/// can be used as inputs. Any change in setting of the I/Os as either
/// inputs or outputs can be done with the write mode. If a high is applied
/// externally to an I/O that has been written earlier to low, a large
/// current (IOL) flows to GND.<br>
/// <br>
/// The fixed I2C address of the PCF8575C (0x20) is the same as the PCF8575,
/// PCF8574, PCA9535, and PCA9555, allowing up to eight of these devices,
/// in any combination, to share the same I2C bus or SMBus.
/// \par Schematic
///   \verbinclude SCHEMATIC
/// \par Caveats
///   Conforms to Arduino IDE 1.5 Library Specification v2.1 which requires
///   Arduino IDE >= 1.5.
/// \par Support
/// Please [submit an issue](https://github.com/4-20ma/I2cDiscreteIoExpander/
/// issues) for all questions, bug reports, and feature requests. Email
/// requests will be politely redirected to the issue tracker so others may
/// contribute to the discussion and requestors get a more timely response.
/// \author Doc Walker ([4-20ma@wvfans.net](mailto:4-20ma@wvfans.net))
/// \copyright 2009-2016 Doc Walker
/// \par License
/// <pre>
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
/// <span>
///     http://www.apache.org/licenses/LICENSE-2.0
/// <span>
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
/// </pre>


#ifndef I2C_DISCRETE_IO_EXPANDER_H
#define I2C_DISCRETE_IO_EXPANDER_H


// _________________________________________________________ STANDARD INCLUDES
// include types & constants of Wiring core API
#include <Arduino.h>


// __________________________________________________________ PROJECT INCLUDES
// include twi/i2c library
#include <Wire.h>


// ____________________________________________________________ UTILITY MACROS


// _________________________________________________________________ CONSTANTS
/// I2C/TWI success (transaction was successful).
/// \relates I2cDiscreteIoExpander
static const uint8_t TWI_SUCCESS      = 0;


/// I2C/TWI device not present (address sent, NACK received).
/// \relates I2cDiscreteIoExpander
static const uint8_t TWI_DEVICE_NACK  = 2;


/// I2C/TWI data not received (data sent, NACK received).
/// \relates I2cDiscreteIoExpander
static const uint8_t TWI_DATA_NACK    = 3;


/// I2C/TWI other error.
/// \relates I2cDiscreteIoExpander
static const uint8_t TWI_ERROR        = 4;


// _________________________________________________________ CLASS DEFINITIONS
class I2cDiscreteIoExpander
{
  public:
    // ............................................... public member functions
    I2cDiscreteIoExpander(uint8_t);
    I2cDiscreteIoExpander();
    uint8_t  digitalRead();
    uint8_t  digitalWrite(uint16_t);
    uint8_t  getAddress();
    uint16_t getPorts();
    void     enableBitwiseInversion();
    void     disableBitwiseInversion();
    bool     isInverted();

    // ........................................ static public member functions

    // ..................................................... public attributes

    // .............................................. static public attributes

  private:
    // .............................................. private member functions

    // ....................................... static private member functions

    // .................................................... private attributes
    /// Device address as defined by pins A2, A1, A0.
    uint8_t address_;

    /// Storage object for I2cDiscreteIoExpander ports 1 (P17..P10), 0 (P07..P00).
    uint16_t ports_;

    /// Flag indicating whether bits are to be inverted before read/write (false=don't invert, true=invert).
    bool shouldInvert_;

    // ............................................. static private attributes
    /// Factory pre-set slave address.
    static const uint8_t BASE_ADDRESS_ = 0x20;
};
#endif // I2C_DISCRETE_IO_EXPANDER_H
/// \example examples/BareMinimum/BareMinimum.ino
/// \example examples/MultipleDevices/MultipleDevices.ino
