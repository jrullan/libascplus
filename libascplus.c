/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"                      // Include simple tools
#include "ascplus.h"

int main()                                    // Main function
{
  // Add startup code here.
  cog_run(&readAnalogs,128); // Read analog channels into analogCh[] array
 
  while(1)
  {
    // Add main loop code here.
    if(input(2)){
      print("analog[0] = %d \n",getAnalogPercent(0));
      pause(250);
    }
  }  
}
