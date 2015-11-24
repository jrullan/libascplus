#include "simpletools.h"                      // Include simple tools

/*
  Analog read based on a BasicStamp2 code found
  and the documentation for the ASC+ and the MCP3208.

  The Propeller MCU does not have analog inputs. Fortunately,
  the ASC+ (Arduino Shield Compatible Plus) board has an onboard
  A/D converter chip, the MCP3208 that provides 8 analog channels.
  The MCP3208 converts a 0-5V signal into a value of 0-4095 decimal
  in single channel configuration. To read the value you have to
  use the SPI protocol. With the SPI function shift_out
  you can send a request for the value of one channel at the time.
  You use shift_in to receive the value (a 12bit value).

  The propeller pins used for communicating with the MCP3208 are:
  25 Clock (CLK)
  26 Data (DIN and DOUT)
  27 Chip Select (CS)

  For single channel mode you must first set the CS low, then send one high bit
  then four bits for single/diff, B2, B1, B0. B2-B1-B0 specifies the channel
  number to read.

  Author: José Rullán
  Date: 22/11/2015
*/

// SPI pins and constants for the MCP3208 AD Converter in the ASC+
#define CLK 25
#define DIN 26
#define DOUT 26
#define CS 27
#define OFFSET 0b11000   //First channel offset, it means 11000
#define SHIFT_OUT_BITS 5  //Need 5 bits to send Start bit first (MSB first)
#define SHIFT_IN_BITS 13  //Need 13 bits, 1 null + 12 for the value

// If you want a cog to continuously read all channels use these functions
void readAnalogs();         // To be called in a cog_run
int getAnalog(int channel);
int getAnalogPercent(int channel);

// To access the analog channels without using a cog
int analogRead(int channel);