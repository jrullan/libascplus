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

volatile int analogVal[8];  // Array to store analog input channels data

 /* 
  * This function uses SPI to read the analog channels from the ASC+ MCP3208
  * The MCP3208 is powered by 5V and its reference voltage is 5 (see schematic of ASC+)
  * For 5V the value returned will be 4095 (Range 0-4095) in single mode (one pin per channel).
  *
  * Pins used:
  *   CS = 27
  *   DIN/DOUT = 26
  *   CLK = 25
  * 
  * The SPI request command consists of 5 bits:
  *   The first bit sent (B4=16) signals the start of the conversion of the AD
  *   The second bit sent (B3 = 8) signals single channel mode
  *   The other three bits (B2,B1,B0) indicate the channel to read (i.e. 000 = CH0, 011 = CH3)
  * 
  *   Thus, channel selection starts at 24 (11000) // CH0 = 24
  *   Example CH2 would be: 24 + 26 = 10 (11010)
  */
void readAnalogs(){
  while(1)
  {
    //Read all analog channels (0-5)
    for(int ch=0; ch<6; ch++){  
      
      low(CS);                                        // Start SPI request        
      shift_out(DIN,CLK,MSBFIRST,SHIFT_OUT_BITS,OFFSET + ch);     // Request channel value
      analogVal[ch] = shift_in(DOUT,CLK,MSBPOST,SHIFT_IN_BITS);  // Receive value in 13 bits (1 Null + 12 data) (specific for the MCP3208)
      high(CS);                                       // End request
      
      //analogVal[ch] = analogRead(ch);
    }
  }
}

// read analog value (0-4095)
int getAnalog(int channel){
  if(channel >= 0 && channel < 6)return analogVal[channel];
  return -1;
}

// read analog value in percent (0-100)
int getAnalogPercent(int channel){
  if(channel >= 0 && channel < 6)return analogVal[channel]*100/4095;
  return -1;
}

