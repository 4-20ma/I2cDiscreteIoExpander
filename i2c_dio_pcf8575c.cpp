/*
  
  i2c_dio_pcf8575c.cpp - Arduino library for TI PCF8575C 16-bit I2C I/O expander
  
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


/* _____PROJECT INCLUDES_____________________________________________________ */
#include "i2c_dio_pcf8575c.h"


/* _____PUBLIC FUNCTIONS_____________________________________________________ */
/**
Create class object
*/
i2c_dio_pcf8575c::i2c_dio_pcf8575c()
{
}


/**
Initialize class object.

Sets device ID, enables bitwise inversion, resets storage object, and 
sets up the TWI/I2C interface. Call once class has been instantiated, 
typically within setup().
*/
void i2c_dio_pcf8575c::begin(uint8_t u8DeviceID)
{
  _u8DeviceID = u8DeviceID & 0b111;
  enableBitwiseInversion();
  data = 0;
  Wire.begin();
}


/**
Initialize class object.

Sets default device ID to ku8DeviceID0. Call once class has been 
instantiated, typically within setup().

@overload i2c_dio_pcf8575c::begin()
*/
void i2c_dio_pcf8575c::begin()
{
  begin(ku8DeviceID0);
}


/**
Retrieve discrete values from device.

@return 0 on success; exception number on failure
*/
uint8_t i2c_dio_pcf8575c::digitalRead()
{
  uint8_t hi, lo, u8Status;
  
  Wire.beginTransmission(_ku8BaseAddress | _u8DeviceID);
  u8Status = Wire.endTransmission();
  
  if (u8Status == ku8TWISuccess)
  {
    if (Wire.requestFrom(_ku8BaseAddress | _u8DeviceID, 2) == 2)
    {
      lo = Wire.receive();
      hi = Wire.receive();
      data = _bInvert ? word(~hi, ~lo) : word(hi, lo);
    }
    else
    {
      return ku8TWIError;
    }
  }
  
  return u8Status;
}


/**
Write discrete values to device.

@return 0 on success; exception number on failure
*/
uint8_t i2c_dio_pcf8575c::digitalWrite()
{
  Wire.beginTransmission(_ku8BaseAddress | _u8DeviceID);
  Wire.send(lowByte(_bInvert ? ~data : data));
  Wire.send(highByte(_bInvert ? ~data : data));
  
  return Wire.endTransmission();
}


/**
Write discrete values to device.

@overload i2c_dio_pcf8575c::digitalWrite(uint16_t u16Data)
@param u16Data word to be written to device (0x0000..0xFFFF)
@return 0 on success; exception number on failure
*/
uint8_t i2c_dio_pcf8575c::digitalWrite(uint16_t u16Data)
{
  data = u16Data;
  return digitalWrite();
}


/**
Retrieve device ID.

@return ID of device (0..7)
*/
uint8_t i2c_dio_pcf8575c::id()
{
  return _u8DeviceID;
}


/**
Enable bitwise inversion; all bits will be inverted prior to future read/write operations.

@see i2c_dio_pcf8575c::isInverted()
*/
void i2c_dio_pcf8575c::enableBitwiseInversion()
{
  data = _bInvert ? data : ~data;
  _bInvert = true;
}


/**
Disable bitwise inversion; bits will not be inverted prior to future read/write operations.

@see i2c_dio_pcf8575c::isInverted()
*/
void i2c_dio_pcf8575c::disableBitwiseInversion()
{
  data = _bInvert ? ~data : data;
  _bInvert = false;
}


/**
Indicate whether bitwise inversion is enabled.

@return status of bitwise inversion (false=don't invert, true=invert)
@see i2c_dio_pcf8575c::enableBitwiseInversion()
@see i2c_dio_pcf8575c::disableBitwiseInversion()
*/
bool i2c_dio_pcf8575c::isInverted()
{
  return _bInvert;
}

