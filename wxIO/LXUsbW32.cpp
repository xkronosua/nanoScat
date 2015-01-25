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
 * @file           LXUsbW32.cpp
 *****************************************************************************
 * class LXUsbW32
 *
 * Shoestring Astronomy Appliance driver for the LXUSB product
 * Win32 upper level driver
 *
 * Defines the Win32 upper level driver
 *  this class is derived from the interface class LXUsb
 *  it implements the API style interface which is OS dependent
 *  This is the Win32 implementation using SAUSB_LibHid
 *
 * This is part of the Webcam Driver Library of wxAstroCapture
 *
 * Copyright (C) 2009 Martin Burri  (bm98@burri-web.org)
 *
 * Pls see notes in SAUSB_LibHid.h for information about requirements
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

#ifdef WIN32

#include "LXUsbW32.h"

#include "SAUSB_LibHid.h"  // the lower level driver
#pragma comment (lib,"SAUSB_LibHid.lib")


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// define the LXUSB Bits
#define F1   0x01
#define F2   0x02
#define SHUT 0x04
#define AMP  0x08
#define CTRL 0x0f

#define LRED 0x10
#define LON  0x20
#define LED  0x30

#define CRLLED  0x3f


LXUsbW32::LXUsbW32()
: m_p_lxusb(NULL)
{
   //ctor
   if ( SAUSB_LibHid::DeviceAttached(SAUSB_LibHid::SAUSB_LXUSB) ) {
      m_p_lxusb = new SAUSB_LibHid;
      if (m_p_lxusb) {
         m_board_present = this->LXUSB_Open();
         if (m_board_present) {
            this->LXUSB_Reset();
            this->LXUSB_LEDOff(); // Switch LED off when enabled
            this->LXUSB_Close();
         }
      }
   }
}

LXUsbW32::~LXUsbW32()
{
   this->LXUSB_Reset();
   this->LXUSB_Close();
   if (m_p_lxusb) delete m_p_lxusb; m_p_lxusb=NULL;
}

/// @brief Sleep for an amount of milliseconds
void LXUsbW32::Sleep_ms(unsigned short  mseconds)
{
	SAUSB_LibHid::Sleep_ms(mseconds);
}


/// LXUSB Win API style interface

bool LXUsbW32::LXUSB_Open( void )
{
   if (!m_p_lxusb) return false;

   int retVal=m_p_lxusb->DeviceOpen(SAUSB_LibHid::SAUSB_LXUSB);
   if ( retVal < SAUSB_LibHid::USB_OK ) return false;

   retVal = m_p_lxusb->ReadByte(m_ctrl); // get actual control byte
   if ( retVal < SAUSB_LibHid::USB_OK ) return false;

   m_ctrl &= CRLLED; // mask used bits
   return true;
}

bool LXUsbW32::LXUSB_Close( void )
{
   if (!m_p_lxusb) return false;

   int retVal=m_p_lxusb->DeviceClose();
   if ( retVal < SAUSB_LibHid::USB_OK ) return false;

   return true;
}

bool LXUsbW32::LXUSB_Reset( void )
{
   if (!m_p_lxusb) return false;

   m_ctrl = LED; // directions off, red LED
   return (m_p_lxusb->WriteByte(m_ctrl) >= SAUSB_LibHid::USB_OK);
}

bool LXUsbW32::LXUSB_Frame1Assert( void )
{
   if (!m_p_lxusb) return false;

   m_ctrl |= F1; // set Frame1
   return (m_p_lxusb->WriteByte(m_ctrl) >= SAUSB_LibHid::USB_OK);
}

bool LXUsbW32::LXUSB_Frame1Deassert( void )
{
   if (!m_p_lxusb) return false;

   m_ctrl &= ~F1; // reset Frame1
   return (m_p_lxusb->WriteByte(m_ctrl) >= SAUSB_LibHid::USB_OK);
}

bool LXUsbW32::LXUSB_Frame2Assert( void )
{
   if (!m_p_lxusb) return false;

   m_ctrl |= F2; // set Frame2
   return (m_p_lxusb->WriteByte(m_ctrl) >= SAUSB_LibHid::USB_OK);
}

bool LXUsbW32::LXUSB_Frame2Deassert( void )
{
   if (!m_p_lxusb) return false;

   m_ctrl &= ~F2; // reset Frame2
   return (m_p_lxusb->WriteByte(m_ctrl) >= SAUSB_LibHid::USB_OK);
}

bool LXUsbW32::LXUSB_ShutterAssert( void )
{
   if (!m_p_lxusb) return false;

   m_ctrl |= SHUT; // set Shutter
   return (m_p_lxusb->WriteByte(m_ctrl) >= SAUSB_LibHid::USB_OK);
}

bool LXUsbW32::LXUSB_ShutterDeassert( void )
{
   if (!m_p_lxusb) return false;

   m_ctrl &= ~SHUT; // reset Shutter
   return (m_p_lxusb->WriteByte(m_ctrl) >= SAUSB_LibHid::USB_OK);
}

bool LXUsbW32::LXUSB_CCDAmpAssert( void )
{
   if (!m_p_lxusb) return false;

   m_ctrl |= AMP; // set Amp
   return (m_p_lxusb->WriteByte(m_ctrl) >= SAUSB_LibHid::USB_OK);
}

bool LXUsbW32::LXUSB_CCDAmpDeassert( void )
{
   if (!m_p_lxusb) return false;

   m_ctrl &= ~AMP; // reset Amp
   return (m_p_lxusb->WriteByte(m_ctrl) >= SAUSB_LibHid::USB_OK);
}

bool LXUsbW32::LXUSB_AllControlDeassert( void )
{
   if (!m_p_lxusb) return false;

   m_ctrl &= LED; // reset all but LED
   return (m_p_lxusb->WriteByte(m_ctrl) >= SAUSB_LibHid::USB_OK);
}

bool LXUsbW32::LXUSB_LEDOn( void )
{
   if (!m_p_lxusb) return false;

   m_ctrl |= LON; // set LED ON
   return (m_p_lxusb->WriteByte(m_ctrl) >= SAUSB_LibHid::USB_OK);
}

bool LXUsbW32::LXUSB_LEDOff( void )
{
   if (!m_p_lxusb) return false;

   m_ctrl &= ~LON; // set LED OFF
   return (m_p_lxusb->WriteByte(m_ctrl) >= SAUSB_LibHid::USB_OK);
}

bool LXUsbW32::LXUSB_LEDRed( void )
{
   if (!m_p_lxusb) return false;

   m_ctrl |= LRED; // set LED red
   return (m_p_lxusb->WriteByte(m_ctrl) >= SAUSB_LibHid::USB_OK);
}

bool LXUsbW32::LXUSB_LEDGreen( void )
{
   if (!m_p_lxusb) return false;

   m_ctrl &= ~LRED; // set LED NOT red
   return (m_p_lxusb->WriteByte(m_ctrl) >= SAUSB_LibHid::USB_OK);
}

bool LXUsbW32::LXUSB_SetAll( int frame1, int frame2, int shutter, int ccdamp, int led )
{
   if (!m_p_lxusb) return false;

   m_ctrl = 0x00;
   if (frame1==LXUSB_FRAME1_ASSERTED) m_ctrl |=F1;
   if (frame2==LXUSB_FRAME2_ASSERTED) m_ctrl |=F2;
   if (shutter==LXUSB_SHUTTER_ASSERTED) m_ctrl |=SHUT;
   if (ccdamp==LXUSB_CCDAMP_ASSERTED) m_ctrl |=AMP;
   if ( (led==LXUSB_LED_ON_RED) || (led==LXUSB_LED_OFF_RED) ) m_ctrl |=LRED;
   if ( (led==LXUSB_LED_ON_RED) || (led==LXUSB_LED_ON_GREEN) ) m_ctrl |=LON;
   return (m_p_lxusb->WriteByte(m_ctrl) >= SAUSB_LibHid::USB_OK);
}

bool LXUsbW32::LXUSB_Frame1Status( int *status )
{
   if (!m_p_lxusb) return false;

   bool  retVal = ( SAUSB_LibHid::USB_OK==m_p_lxusb->ReadByte(m_ctrl) );
   *status = ((m_ctrl&F1)==F1) ? LXUSB_FRAME1_ASSERTED : LXUSB_FRAME1_DEASSERTED;
   return retVal;
}

bool LXUsbW32::LXUSB_Frame2Status( int *status )
{
   if (!m_p_lxusb) return false;

   bool  retVal = ( SAUSB_LibHid::USB_OK==m_p_lxusb->ReadByte(m_ctrl) );
   *status = ((m_ctrl&F2)==F2) ? LXUSB_FRAME2_ASSERTED : LXUSB_FRAME2_DEASSERTED;
   return retVal;
}

bool LXUsbW32::LXUSB_ShutterStatus( int *status )
{
   if (!m_p_lxusb) return false;

   bool  retVal = ( SAUSB_LibHid::USB_OK==m_p_lxusb->ReadByte(m_ctrl) );
   *status = ((m_ctrl&SHUT)==SHUT) ? LXUSB_SHUTTER_ASSERTED : LXUSB_SHUTTER_DEASSERTED;
   return retVal;
}

bool LXUsbW32::LXUSB_CCDAmpStatus( int *status )
{
   if (!m_p_lxusb) return false;

   bool  retVal = ( SAUSB_LibHid::USB_OK==m_p_lxusb->ReadByte(m_ctrl) );
   *status = ((m_ctrl&AMP)==AMP) ? LXUSB_CCDAMP_ASSERTED : LXUSB_CCDAMP_DEASSERTED;
   return retVal;
}

bool LXUsbW32::LXUSB_LEDStatus( int *status )
{
   if (!m_p_lxusb) return false;

   bool  retVal = ( SAUSB_LibHid::USB_OK==m_p_lxusb->ReadByte(m_ctrl) );
   *status = ( (m_ctrl&LON)==LON ) ? ( ( (m_ctrl&LRED)==LRED ) ? LXUSB_LED_ON_RED  : LXUSB_LED_ON_GREEN )  \
                                   : ( ( (m_ctrl&LRED)==LRED ) ? LXUSB_LED_OFF_RED : LXUSB_LED_OFF_GREEN ) ;
   return retVal;
}

bool LXUsbW32::LXUSB_Status( int *frame1_status, int *frame2_status, int *shutter_status, int *ccdamp_status, int *led_status )
{
   if (!m_p_lxusb) return false;

   bool  retVal = ( SAUSB_LibHid::USB_OK==m_p_lxusb->ReadByte(m_ctrl) );
   *frame1_status = ((m_ctrl&F1)==F1) ? LXUSB_FRAME1_ASSERTED : LXUSB_FRAME1_DEASSERTED;
   *frame2_status = ((m_ctrl&F2)==F2) ? LXUSB_FRAME2_ASSERTED : LXUSB_FRAME2_DEASSERTED;
   *shutter_status = ((m_ctrl&SHUT)==SHUT) ? LXUSB_SHUTTER_ASSERTED : LXUSB_SHUTTER_DEASSERTED;
   *ccdamp_status = ((m_ctrl&AMP)==AMP) ? LXUSB_CCDAMP_ASSERTED : LXUSB_CCDAMP_DEASSERTED;
   *led_status = ( (m_ctrl&LON)==LON ) ? ( ( (m_ctrl&LRED)==LRED ) ? LXUSB_LED_ON_RED  : LXUSB_LED_ON_GREEN )  \
                                       : ( ( (m_ctrl&LRED)==LRED ) ? LXUSB_LED_OFF_RED : LXUSB_LED_OFF_GREEN ) ;
   return retVal;
}


#endif // WIN32

