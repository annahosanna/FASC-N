/*******************************************************************
*
* This function was developed on an Intel architecture. The big endian once little
* endian issues must match the bit flow as if it were a communications stream. That is, the
* fist bits to flow would be in character array location 0.
*
* The FASC-N encodes information as five-bit groups that are concatenated into as 25-Byte
* value. The purpose of the expand_fascn() function is to take the 25-byte FASC-N and expand it
* into a 40-Byte character array.

This function requires the value of error to be defined externally
*
********************************************************************/

#ifndef expandFascn_h
#define expandFascn_h

int expand_fascn( char fascn25[25], char fascn40[40] );

#endif
