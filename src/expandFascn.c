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
#define msk 0x80 /* this is the most significant bit mask */
#define addBit 0x01 /* this is a character with the least significant bit set */

#include "errorCode.h"

int expand_fascn(fascn25, fascn40)
 char fascn25[25], fascn40[40];
 {
 int byte_count, bit_count, bit_index, expanded_index;
 char temp, temp2=0;


 for (bit_count = 0, byte_count = 0, expanded_index=0; byte_count < 25; byte_count++) {
   temp = fascn25[byte_count];
   for (bit_index=0; bit_index < 8; bit_index++) {
    if (msk & temp) {   /* is the most significant bit in temp a 1? */
      temp2 ^= addBit;  /* Then change the least significant bit in temp2 to a 1 */
      }

    temp <<= 1; /* shift left to prepare the next bit for testing */

    bit_count += 1;
    if ((bit_count % 5)== 0) { /* is this the 5th 1 or 0 printed? */
      temp2= convertCharacter(temp2);

      if (temp2==errorCode) {
        return(1);
        }
      fascn40[expanded_index] = temp2; /* over write with value */
      expanded_index += 1; /* increment the expanded index */
      temp2 = 0;
      } /* end if */
     temp2 <<= 1;
     } /* end inner for loop */
   } /* end for */
  return(0);
 }
