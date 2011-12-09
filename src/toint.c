
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

int toint(ch)
  char ch;
{
  int return_value;
  switch (ch) {
  case '0': { return_value = 0;
    break; }
  case '1': { return_value = 1;
    break; }
  case '2': { return_value = 2;
    break; }
  case '3': { return_value = 3;
    break; }
  case '4': { return_value = 4;
    break; }
  case '5': { return_value = 5;
    break; }
  case '6': { return_value = 6;
    break; }
  case '7': { return_value = 7;
    break; }
  case '8': { return_value = 8;
    break; }
  case '9': { return_value = 9;
    break; }
  default: return_value = 0;
  }
  return(return_value);
}
