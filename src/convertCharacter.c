/*************************************************

The convert number uses the PACS table as a
conversion function. This is a diagnostic function to display the
FASC-N values as characters.

Dependencies:

The external value for error must be defined

*************************************************/

 char convertCharacter(number)
  char  number;

{

  char return_value;
  switch (number) {
  case 0x01: { return_value = '0'; /* 0000 0001 */
              break; }
  case 0x10: { return_value = '1'; /* 0001 0000 */
              break; }
  case 0x08: { return_value = '2'; /* 0000 1000 */
              break; }
  case 0x19: { return_value = '3'; /* 0001 1001 */
              break; }
  case 0x04: { return_value = '4'; /* 0000 0100 */
              break; }
  case 0x15: { return_value = '5'; /* 0001 0101 */
              break; }
  case 0x0d: { return_value = '6'; /* 0000 1101 */
              break; }
  case 0x1c: { return_value = '7'; /* 0001 1100 */
              break; }
  case 0x02: { return_value = '8'; /* 0000 0010 */
              break; }
  case 0x13: { return_value = '9'; /* 0001 0011 */
              break; }
  case 0x1a:   { return_value = 'S'; /* Start Sentinel 0001 1010 */
              break; }
  case 0x16:   { return_value = 'F'; /* Field Separator 0001 0110 */
              break; }
  case 0x1f:   { return_value = 'E'; /* End Sentinel 0001 1111 */
              break; }
  default:   { return_value = error; /* not a valid character */
              break; }
 }
   return(return_value);
}

