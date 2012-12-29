/// \file
/// Arduino library for TI PCF8575C 16-bit I2C I/O expander.
/*
  
  i2c_dio_pcf8575c.h Arduino library for TI PCF8575C 16-bit I2C I/O expander
  
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
/// current (IOL) flows to GND.
/// \author Doc Walker
/// \version \verbinclude VERSION
/// \date 29 Dec 2012
/// \copyright GNU General Public License v3
/// \par Source Code Repository:
///   https://github.com/4-20ma/i2c_dio_pcf8575c
/// \par Programming Style Guidelines:
///   http://geosoft.no/development/cppstyle.html
/// \par Schematic:
///   \verbinclude SCHEMATIC


#ifndef i2c_dio_pcf8575c_h
#define i2c_dio_pcf8575c_h


// _________________________________________________________ STANDARD INCLUDES
// include types & constants of Wiring core API
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


// __________________________________________________________ PROJECT INCLUDES
// include twi/i2c library
#include <Wire.h>


// ____________________________________________________________ UTILITY MACROS


// _________________________________________________________________ CONSTANTS


// _________________________________________________________ CLASS DEFINITIONS
class i2c_dio_pcf8575c
{
  public:
    // ............................................... public member functions
    i2c_dio_pcf8575c();
    
    void     begin(uint8_t);
    void     begin();
    uint8_t  digitalRead();
    uint8_t  digitalWrite();
    uint8_t  digitalWrite(uint16_t);
    uint8_t  id();
    void     enableBitwiseInversion();
    void     disableBitwiseInversion();
    bool     isInverted();
    
    // ........................................ static public member functions
    
    // ..................................................... public attributes
    /// Storage object for state of PCF8575C.
    /// \par Usage:
    /// \code
    /// ...
    /// \endcode
    uint16_t data;
    
    // .............................................. static public attributes
    
    /**
    I2C address offset for PCF8575C module (A2=0, A1=0, A0=0).
    */
    static const uint8_t ku8DeviceID0                    = 0b000;
    
    /**
    I2C address offset for PCF8575C module (A2=0, A1=0, A0=1).
    */
    static const uint8_t ku8DeviceID1                    = 0b001;
    
    /**
    I2C address offset for PCF8575C module (A2=0, A1=1, A0=0).
    */
    static const uint8_t ku8DeviceID2                    = 0b010;
    
    /**
    I2C address offset for PCF8575C module (A2=0, A1=1, A0=1).
    */
    static const uint8_t ku8DeviceID3                    = 0b011;
    
    /**
    I2C address offset for PCF8575C module (A2=1, A1=0, A0=0).
    */
    static const uint8_t ku8DeviceID4                    = 0b100;
    
    /**
    I2C address offset for PCF8575C module (A2=1, A1=0, A0=1).
    */
    static const uint8_t ku8DeviceID5                    = 0b101;
    
    /**
    I2C address offset for PCF8575C module (A2=1, A1=1, A0=0).
    */
    static const uint8_t ku8DeviceID6                    = 0b110;
    
    /**
    I2C address offset for PCF8575C module (A2=1, A1=1, A0=1).
    */
    static const uint8_t ku8DeviceID7                    = 0b111;
    
    /**
    I2C/TWI success (transaction was successful).
    */
    static const uint8_t ku8TWISuccess                   = 0;
    
    /**
    I2C/TWI device not present (address sent, NACK received).
    */
    static const uint8_t ku8TWIDeviceNACK                = 2;
    
    /**
    I2C/TWI data not received (data sent, NACK received).
    */
    static const uint8_t ku8TWIDataNACK                  = 3;
    
    /**
    I2C/TWI other error.
    */
    static const uint8_t ku8TWIError                     = 4;
    
  private:
    // .............................................. private member functions
    
    // ....................................... static private member functions
    
    // .................................................... private attributes
    
    // ............................................. static private attributes
    /**
    I2C base address for the PCF8575C module.
    */
    static const uint8_t _ku8BaseAddress                 = 0x20;
    
    /**
    Device ID (set by pins A2, A1, A0).
    */
    uint8_t _u8DeviceID;
    
    /**
    Flag indicating whether bits are to be inverted before read/write (false=don't invert, true=invert).
    */
    bool _bInvert;
};
#endif
/// \example examples/PCF8575C_example/PCF8575C_example.pde
/// \example examples/Marching_ants_example/Marching_ants_example.pde
