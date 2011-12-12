/************************************************************************

As noted in the Technical Implementation Guidance:
Smart Card Enabled Physical Access Control Systems

AGENCY CODE

Identifies the government agency issuing the credential


Dependencies:

Requires the toint() function that converts a character in the range '0' to '9' to an integer.
If the character converted is not '0' - '9' the function returns a value of 0.

************************************************************************/

#include "agencyCode.h"

int agency_code( char fascn[40] )
{
  int temp;
  temp = toint(fascn[1]) * 1000;
  temp += toint(fascn[2]) * 100;
  temp += toint(fascn[3]) * 10;
  temp += toint(fascn[4]);
  return(temp);
}
