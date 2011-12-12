
/********************************************************************

This function converts a text character to an integer. Same function as found
in ctype.h

Note:

In SP 800-87 rev 1, many of the agency codes include the hexadecimal values
in the range 'A' to 'F'. However, the Technical Implementation Guidance:
Smart Card Enabled Physical Access Control Systems [PACS] uses the table below.
Thus, the FASC-N only recognizes 0 - 9. Moreover, the values for the Start Sentinel,
Field Separator, and End Sentinel correspond to three of these BCD values so they
cannot be used. Consequently, the default return is a "0" if the character is
unrecognized.

********************************************************************/

#ifndef toint_h
#define toint_h

int toint( char ch );

#endif
