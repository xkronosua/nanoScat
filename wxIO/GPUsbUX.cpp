/**

  Shoestring Appliance - Control Library

Copyright (C) 2009 Martin Burri  (bm@burri-web.org)

This program is free software licensed under LGPL;
you can redistribute it and/or modify it under the terms of
the GNU Lesser General Public License as published by the
Free Software Foundation; either version 3 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

/**
 * @file           GPUsbUX.cpp
 *****************************************************************************
 * class GPUsbUX
 *
 * Shoestring Astronomy Appliance driver for the GPUSB product
 * Linux upper level driver - Similar to the original DLL API
 *
 * Implements the Linux upper level driver
 *
 * This is part of the Guiding Driver Library of wxAstroCapture
 *
 * Copyright (C) 2009 Martin Burri  (bm98@burri-web.org)
 *
 * Pls see notes in SAUSB_LibUsb for information about requirements
 *
 *<hr>
 *
 * @b Project      wxAstroCapture<br>
 *
 * @author         M. Burri
 * @date           10-Jan-2009
 *
 *****************************************************************************
 *<hr>
 * @b Updates
 * - dd-mmm-yyyy V. Name: Description
 *
 *****************************************************************************/
#ifndef WIN32

#include "GPUsbUX.h"

#include "SAUSB_LibUsb.h"  // the lower level driver

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// define the GPUSB Bits
#define RAM  0x01
#define RAP  0x02
#define DEM  0x04
#define DEP  0x08
#define RADE 0x0f

#define LRED 0x10
#define LON  0x20
#define LED  0x30

#define RADELED  0x3f


GPUsbUX::GPUsbUX()
: m_p_gpusb(NULL)
{
   //ctor
   if ( SAUSB_LibUsb::DeviceAttached(SAUSB_LibUsb::SAUSB_GPUSB) ) {
      m_p_gpusb = new SAUSB_LibUsb;
      if (m_p_gpusb) {
         m_board_present = this->GPUSB_Open();
         if (m_board_present) {
            this->GPUSB_Reset();
            this->GPUSB_LEDOff(); // Switch LED off when enabled
            this->GPUSB_Close();
         }
      }
   }
}

GPUsbUX::~GPUsbUX()
{
   this->GPUSB_Reset();
   this->GPUSB_Close();
   if (m_p_gpusb) delete m_p_gpusb; m_p_gpusb=NULL;
}

/// GPUSB Win API style interface


/// @brief Sleep for an amount of milliseconds
void GPUsbUX::Sleep_ms(unsigned short  mseconds)
{
	if (m_p_gpusb) m_p_gpusb->Sleep_ms(mseconds);
}

bool GPUsbUX::GPUSB_Open( void )
{
   if (!m_p_gpusb) return false;

   int retVal=m_p_gpusb->DeviceOpen(SAUSB_LibUsb::SAUSB_GPUSB);
   if ( retVal < SAUSB_LibUsb::USB_OK ) return false;

   retVal = m_p_gpusb->ReadByte(m_ctrl); // get actual control byte
   if ( retVal < SAUSB_LibUsb::USB_OK ) return false;

   m_ctrl &= RADELED; // mask used bits
   return true;
}

bool GPUsbUX::GPUSB_Close( void )
{
   if (!m_p_gpusb) return false;

   int retVal=m_p_gpusb->DeviceClose();
   if ( retVal < SAUSB_LibUsb::USB_OK ) return false;

   return true;
}

bool GPUsbUX::GPUSB_Reset( void )
{
   if (!m_p_gpusb) return false;

   m_ctrl = LED; // directions off, red LED
   return (m_p_gpusb->WriteByte(m_ctrl) >= SAUSB_LibUsb::USB_OK);
}

bool GPUsbUX::GPUSB_RAMAssert( void )
{
   if (!m_p_gpusb) return false;

   m_ctrl |= RAM; // set RA-
   return (m_p_gpusb->WriteByte(m_ctrl) >= SAUSB_LibUsb::USB_OK);
}

bool GPUsbUX::GPUSB_RAMDeassert( void )
{
   if (!m_p_gpusb) return false;

   m_ctrl &= ~RAM; // reset RA-
   return (m_p_gpusb->WriteByte(m_ctrl) >= SAUSB_LibUsb::USB_OK);
}

bool GPUsbUX::GPUSB_RAPAssert( void )
{
   if (!m_p_gpusb) return false;

   m_ctrl |= RAP; // set RA+
   return (m_p_gpusb->WriteByte(m_ctrl) >= SAUSB_LibUsb::USB_OK);
}

bool GPUsbUX::GPUSB_RAPDeassert( void )
{
   if (!m_p_gpusb) return false;

   m_ctrl &= ~RAP; // reset RA+
   return (m_p_gpusb->WriteByte(m_ctrl) >= SAUSB_LibUsb::USB_OK);
}

bool GPUsbUX::GPUSB_DecMAssert( void )
{
   if (!m_p_gpusb) return false;

   m_ctrl |= DEM; // set DEC-
   return (m_p_gpusb->WriteByte(m_ctrl) >= SAUSB_LibUsb::USB_OK);
}

bool GPUsbUX::GPUSB_DecMDeassert( void )
{
   if (!m_p_gpusb) return false;

   m_ctrl &= ~DEM; // reset DEC-
   return (m_p_gpusb->WriteByte(m_ctrl) >= SAUSB_LibUsb::USB_OK);
}

bool GPUsbUX::GPUSB_DecPAssert( void )
{
   if (!m_p_gpusb) return false;

   m_ctrl |= DEP; // set DEC+
   return (m_p_gpusb->WriteByte(m_ctrl) >= SAUSB_LibUsb::USB_OK);
}

bool GPUsbUX::GPUSB_DecPDeassert( void )
{
   if (!m_p_gpusb) return false;

   m_ctrl &= ~DEP; // reset DEC+
   return (m_p_gpusb->WriteByte(m_ctrl) >= SAUSB_LibUsb::USB_OK);
}

bool GPUsbUX::GPUSB_AllDirDeassert( void )
{
   if (!m_p_gpusb) return false;

   m_ctrl &= LED; // reset all but LED
   return (m_p_gpusb->WriteByte(m_ctrl) >= SAUSB_LibUsb::USB_OK);
}

bool GPUsbUX::GPUSB_LEDOn( void )
{
   if (!m_p_gpusb) return false;

   m_ctrl |= LON; // set LED ON
   return (m_p_gpusb->WriteByte(m_ctrl) >= SAUSB_LibUsb::USB_OK);
}

bool GPUsbUX::GPUSB_LEDOff( void )
{
   if (!m_p_gpusb) return false;

   m_ctrl &= ~LON; // set LED OFF
   return (m_p_gpusb->WriteByte(m_ctrl) >= SAUSB_LibUsb::USB_OK);
}

bool GPUsbUX::GPUSB_LEDRed( void )
{
   if (!m_p_gpusb) return false;

   m_ctrl |= LRED; // set LED red
   return (m_p_gpusb->WriteByte(m_ctrl) >= SAUSB_LibUsb::USB_OK);
}

bool GPUsbUX::GPUSB_LEDGreen( void )
{
   if (!m_p_gpusb) return false;

   m_ctrl &= ~LRED; // set LED NOT red
   return (m_p_gpusb->WriteByte(m_ctrl) >= SAUSB_LibUsb::USB_OK);
}

bool GPUsbUX::GPUSB_SetAll( int ram, int rap, int decm, int decp, int led )
{
   if (!m_p_gpusb) return false;

   m_ctrl = 0x00;
   if (ram==GPUSB_RAM_ASSERTED) m_ctrl |=RAM;
   if (rap==GPUSB_RAP_ASSERTED) m_ctrl |=RAP;
   if (decm==GPUSB_DECM_ASSERTED) m_ctrl |=DEM;
   if (decp==GPUSB_DECP_ASSERTED) m_ctrl |=DEP;
   if ( (led==GPUSB_LED_ON_RED) || (led==GPUSB_LED_OFF_RED) ) m_ctrl |=LRED;
   if ( (led==GPUSB_LED_ON_RED) || (led==GPUSB_LED_ON_GREEN) ) m_ctrl |=LON;
   return (m_p_gpusb->WriteByte(m_ctrl) >= SAUSB_LibUsb::USB_OK);
}

bool GPUsbUX::GPUSB_RAMStatus( int *status )
{
   if (!m_p_gpusb) return false;

   bool  retVal = m_p_gpusb->ReadByte(m_ctrl);
   *status = ((m_ctrl&RAM)==RAM) ? GPUSB_RAM_ASSERTED : GPUSB_RAM_DEASSERTED;
   return retVal;
}

bool GPUsbUX::GPUSB_RAPStatus( int *status )
{
   if (!m_p_gpusb) return false;

   bool  retVal = m_p_gpusb->ReadByte(m_ctrl);
   *status = ((m_ctrl&RAP)==RAP) ? GPUSB_RAP_ASSERTED : GPUSB_RAP_DEASSERTED;
   return retVal;
}

bool GPUsbUX::GPUSB_DecMStatus( int *status )
{
   if (!m_p_gpusb) return false;

   bool  retVal = m_p_gpusb->ReadByte(m_ctrl);
   *status = ((m_ctrl&DEM)==DEM) ? GPUSB_DECM_ASSERTED : GPUSB_DECM_DEASSERTED;
   return retVal;
}

bool GPUsbUX::GPUSB_DecPStatus( int *status )
{
   if (!m_p_gpusb) return false;

   bool  retVal = m_p_gpusb->ReadByte(m_ctrl);
   *status = ((m_ctrl&DEP)==DEP) ? GPUSB_DECP_ASSERTED : GPUSB_DECP_DEASSERTED;
   return retVal;
}

bool GPUsbUX::GPUSB_LEDStatus( int *status )
{
   if (!m_p_gpusb) return false;

   bool  retVal = m_p_gpusb->ReadByte(m_ctrl);
   *status = ( (m_ctrl&LON)==LON ) ? ( ( (m_ctrl&LRED)==LRED ) ? GPUSB_LED_ON_RED  : GPUSB_LED_ON_GREEN )  \
                                   : ( ( (m_ctrl&LRED)==LRED ) ? GPUSB_LED_OFF_RED : GPUSB_LED_OFF_GREEN ) ;
   return retVal;
}

bool GPUsbUX::GPUSB_Status( int *ram_status, int *rap_status, int *decm_status, int *decp_status, int *led_status )
{
   if (!m_p_gpusb) return false;

   bool  retVal = m_p_gpusb->ReadByte(m_ctrl);
   *ram_status = ((m_ctrl&RAM)==RAM) ? GPUSB_RAM_ASSERTED : GPUSB_RAM_DEASSERTED;
   *rap_status = ((m_ctrl&RAP)==RAP) ? GPUSB_RAP_ASSERTED : GPUSB_RAP_DEASSERTED;
   *decm_status = ((m_ctrl&DEM)==DEM) ? GPUSB_DECM_ASSERTED : GPUSB_DECM_DEASSERTED;
   *decp_status = ((m_ctrl&DEP)==DEP) ? GPUSB_DECP_ASSERTED : GPUSB_DECP_DEASSERTED;
   *led_status = ( (m_ctrl&LON)==LON ) ? ( ( (m_ctrl&LRED)==LRED ) ? GPUSB_LED_ON_RED  : GPUSB_LED_ON_GREEN )  \
                                       : ( ( (m_ctrl&LRED)==LRED ) ? GPUSB_LED_OFF_RED : GPUSB_LED_OFF_GREEN ) ;
   return retVal;
}

#endif // not WIN32
