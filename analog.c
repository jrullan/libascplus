#include "ascplus.h"

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

// request an analog channel value from the A/D
int analogRead(int ch){
  low(CS);                                                // Start SPI request        
  shift_out(DIN,CLK,MSBFIRST,SHIFT_OUT_BITS,OFFSET + ch); // Request channel value
  int val = shift_in(DOUT,CLK,MSBPOST,SHIFT_IN_BITS);     // Receive value in 13 bits (1 Null + 12 data) (specific for the MCP3208)
  high(CS);                                               // End request
  return val;
}
