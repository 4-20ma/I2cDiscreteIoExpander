/*
  
  I2cIoExpander.cpp - Arduino library for TI PCF8575C 16-bit I2C I/O expander
  
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


// __________________________________________________________ PROJECT INCLUDES
#include "I2cIoExpander.h"


// ___________________________________________________ PUBLIC MEMBER FUNCTIONS
/// Constructor.
/// Assigns device address, resets storage object, enables bitwise inversion.
/// \required Call this to construct I2cIoExpander object.
/// \par Usage:
/// \code
/// ...
/// I2cIoExpander exampleA(1);             // device with address 1
/// I2cIoExpander exampleB[2] = { 2, 3 };  // devices with addresses 2, 3
/// I2cIoExpander exampleC[2] = { I2cIoExpander(4), I2cIoExpander(5) }; // alternate constructor syntax; devices with addresses 4, 5
/// I2cIoExpander exampleD[8] = { 0, 1, 2, 3, 4, 5, 6, 7 }; // addresses 0..7
/// ...
/// \endcode
I2cIoExpander::I2cIoExpander(uint8_t address)
{
  address_ = address & 0b111;
  ports_ = 0;
  shouldInvert_ = true;
}


/// \overload I2cIoExpander::I2cIoExpander(uint8_t address)
/// Constructor.
/// Assigns device address, resets storage object, enables bitwise inversion.
/// \par Usage:
/// \code
/// ...
/// I2cIoExpander device;        // implies device address 0
/// ...
/// \endcode
I2cIoExpander::I2cIoExpander()
{
  address_ = 0;
  ports_ = 0;
  shouldInvert_ = true;
}


/// Retrieve discrete values from device.
/// \required Call this from within \c loop() in order to read from device.
/// \retval 0 success
/// \retval 1 length too long for buffer
/// \retval 2 address send, NACK received <b>(device not on bus)</b>
/// \retval 3 data send, NACK received
/// \retval 4 other twi error (lost bus arbitration, bus error, ...)
/// \par Usage:
/// \code
/// ...
/// I2cIoExpander device;
/// ...
/// uint8_t status = device.digitalRead();
/// if (TWI_SUCCESS == status)
/// {
///   // do something with device.getPorts()
/// }
/// ...
/// \endcode
uint8_t I2cIoExpander::digitalRead()
{
  uint8_t hi, lo, status;
  
  Wire.beginTransmission(BASE_ADDRESS_ | address_);
  status = Wire.endTransmission();
  
  if (TWI_SUCCESS == status)
  {
    if (Wire.requestFrom(BASE_ADDRESS_ | address_, 2) == 2)
    {
      lo = Wire.read();
      hi = Wire.read();
      ports_ = shouldInvert_ ? word(~hi, ~lo) : word(hi, lo);
    }
    else
    {
      return TWI_ERROR;
    }
  }
  
  return status;
}


/// Write discrete values to device.
/// \required Call this from within \c loop() in order to write to device.
/// \param ports word to be written to device (0x0000..0xFFFF)
/// \retval 0 success
/// \retval 1 length too long for buffer
/// \retval 2 address send, NACK received <b>(device not on bus)</b>
/// \retval 3 data send, NACK received
/// \retval 4 other twi error (lost bus arbitration, bus error, ...)
/// \par Usage:
/// \code
/// ...
/// I2cIoExpander device;
/// ...
/// uint8_t status = device.digitalWrite(0xFFFF);
/// if (TWI_SUCCESS == status)
/// {
///   // do something
/// }
/// ...
/// \endcode
uint8_t I2cIoExpander::digitalWrite(uint16_t ports)
{
  ports_ = shouldInvert_ ? ~ports : ports;
  Wire.beginTransmission(BASE_ADDRESS_ | address_);
  Wire.write(lowByte(ports_));
  Wire.write(highByte(ports_));
  // Wire.write(lowByte(shouldInvert_ ? ~ports_ : ports_));
  // Wire.write(highByte(shouldInvert_ ? ~ports_ : ports_));
  
  return Wire.endTransmission();
}


/// Retrieve device address.
/// \optional This function is for testing and troubleshooting.
/// \return address of device (0..7)
/// \par Usage:
/// \code
/// ...
/// I2cIoExpander device;
/// ...
/// address = device.getAddress();
/// ...
/// \endcode
uint8_t I2cIoExpander::getAddress()
{
  return address_;
}


/// Retrieve ports 1 (P17..P10), 0 (P07..P00).
/// \required Call this from within \c loop() to retrieve ports.
/// \return ports of device (0x0000..0xFFFF)
/// \par Usage:
/// \code
/// ...
/// I2cIoExpander device;
/// ...
/// ports = device.getPorts();
/// ...
/// \endcode
uint16_t I2cIoExpander::getPorts()
{
  return ports_;
}


/// Enable bitwise inversion.
/// All bits will be inverted prior to future read/write operations.
/// \par Usage:
/// \code
/// ...
/// I2cIoExpander device;
/// ...
/// device.enableBitwiseInversion();      // bits will now inverted
/// ...
/// \endcode
/// \sa I2cIoExpander::disableBitwiseInversion()
/// \sa I2cIoExpander::isInverted()
void I2cIoExpander::enableBitwiseInversion()
{
  ports_ = shouldInvert_ ? ports_ : ~ports_;
  shouldInvert_ = true;
}


/// Disable bitwise inversion.
/// Bits will not be inverted prior to future read/write operations.
/// \par Usage:
/// \code
/// ...
/// I2cIoExpander device;
/// ...
/// device.disableBitwiseInversion();     // bits will no longer be inverted
/// ...
/// \endcode
/// \sa I2cIoExpander::enableBitwiseInversion()
/// \sa I2cIoExpander::isInverted()
void I2cIoExpander::disableBitwiseInversion()
{
  ports_ = shouldInvert_ ? ~ports_ : ports_;
  shouldInvert_ = false;
}


/// Indicate whether bitwise inversion is enabled.
/// \return status of bitwise inversion (false=not inverted, true=inverted)
/// \par Usage:
/// \code
/// ...
/// I2cIoExpander device;
/// ...
/// if (device.isInverted())
/// {
///   // do something
/// }
/// ...
/// \endcode
/// \sa I2cIoExpander::enableBitwiseInversion()
/// \sa I2cIoExpander::disableBitwiseInversion()
bool I2cIoExpander::isInverted()
{
  return shouldInvert_;
}


// _________________________________________________ STATIC PRIVATE ATTRIBTUES
