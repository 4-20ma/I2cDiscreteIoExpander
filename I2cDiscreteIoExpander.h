/// \file
/// Arduino library for TI PCF8575C 16-bit I2C I/O expander.
/*
  
  I2cDiscreteIoExpander.h Arduino library for TI PCF8575C 16-bit I2C I/O expander
  
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


/// \mainpage Arduino library for TI PCF8575C 16-bit I2C I/O expander.
/// 
/// The PCF8575C provides general-purpose remote I/O expansion for most
/// microcontroller families via the I2C interface serial clock (SCL) and
/// serial data (SDA).<br>
/// 
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
/// 
/// The fixed I2C address of the PCF8575C is the same as the PCF8575,
/// PCF8574, PCA9535, and PCA9555, allowing up to eight of these devices,
/// in any combination, to share the same I2C bus or SMBus.
/// \author Doc Walker
/// \version \verbinclude VERSION
/// \date 1 Jan 2013
/// \copyright GNU General Public License v3
/// \par Arduino IDE:
///   Requires Arduino 1.0 or later
/// \par Source Code Repository:
///   https://github.com/4-20ma/I2cDiscreteIoExpander
/// \par Programming Style Guidelines:
///   http://geosoft.no/development/cppstyle.html
/// \par Schematic:
///   \verbinclude SCHEMATIC


#ifndef I2C_DISCRETE_IO_EXPANDER_H
#define I2C_DISCRETE_IO_EXPANDER_H


// _________________________________________________________ STANDARD INCLUDES
// include types & constants of Wiring core API
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#error Arduino 1.0 or later is required.
#endif


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
