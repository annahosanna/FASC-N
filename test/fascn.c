

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ss 0x1a /* 0001 1010 */
#define fs 0x16 /* 0001 0110 */
#define es 0x1f /* 0001 1111 */
int debug_count = 0;

char outputString[240];

/*************************************************/
/*                                               */
/* The convert number uses the PACS table as a   */
/* conversion function.                          */
/*                                               */
/*************************************************/

 char convert_number(number)
  char  number;

{
  char return_value;
  switch (number) {
  case '0': { return_value = 0x01; /* 0000 0001 */
              break; }
  case '1': { return_value = 0x10; /* 0001 0000 */
              break; }
  case '2': { return_value = 0x08; /* 0000 1000 */
              break; }
  case '3': { return_value = 0x19; /* 0001 1001 */
              break; }
  case '4': { return_value = 0x04; /* 0000 0100 */
              break; }
  case '5': { return_value = 0x15; /* 0001 0101 */
              break; }
  case '6': { return_value = 0x0d; /* 0000 1101 */
              break; }
  case '7': { return_value = 0x1c; /* 0001 1100 */
              break; }
  case '8': { return_value = 0x02; /* 0000 0010 */
              break; }
  case '9': { return_value = 0x13; /* 0001 0011 */
              break; }
  default: return_value = 0x01; /* make it a 0 if its a BCD from 'A' to 'F' */
 }
   return(return_value);
}


char expanded_fascn[40] =
{ss, 0, 0, 0, 0, fs, 0, 0, 0, 0, fs,
 0, 0, 0, 0, 0, 0, fs, 0, fs, 0, fs,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, es, 0}; /* total of 40 digits */

char padded_fascn[25];
#define mask 0x80     /* Most significant bit mask */
#define add_bit 0x01  /* add one bit */

/******************************************/
/*                                        */
/* The padd_fascn function moves the 40   */
/* digit FASC-N to a 25-byte array.       */
/*                                        */
/******************************************/

int padd_function()
{
 int padd_index;
 char temp = 0;
 int char_index = 0;
 int bit_count = 0;
 int bit_index = 0;
 temp = (expanded_fascn[0] << 3);

 /* Step through each byte in the 25-byte FASC-N */

 for (padd_index = 0; padd_index < 25; padd_index++)
  {

   /* For each byte in the FASC-N, step through each bit */

   for(bit_index = 0; bit_index < 8; bit_index++)
   {

   /* test the most significant bit. The left shify places a 0 in the least */
   /* significant bit location.                                             */

   padded_fascn[padd_index] <<= 1; /* left shift */

   /* Test the most significant bit by using an AND test with mask */
   /* If the test is true, add a 1 (change the least significant   */
   /* bit from a 0 to a 1.                                         */

    if (temp & mask) {
      padded_fascn[padd_index] ^= add_bit; /* xor on a bit */
      }

    /* Left shift the temp character to prepare for the next bit test */

    temp <<= 1;

    /* increment the bit counter to see if we need to load the next character */
    /* Note that as the next character is loaded, it is shifter three places  */
    /* to the left to align the most significant bit with the mask            */

    bit_count += 1;
    if(bit_count == 5) {
  bit_count = 0; /* reset bit counter */
  char_index += 1; /* move to the next character */
  if (char_index < 40) /* we don't need a buffer overflow */
    temp = (expanded_fascn[char_index] << 3);
    }
   } /* end  bit_index for */
  } /* end padd_index for */
  return(0);
}

/*******************************************************************/
/*                                                                 */
/* The purpose of the print_bits() function is to convert the      */
/* 25-byte FASC-N into a 5-bit group printout to verify it         */
/* against the Smart Card Enabled Physical Access Control Systems  */
/* example.                                                        */
/*                                                                 */
/*******************************************************************/


int print_bits()
 {
 int byte_count, bit_count, bit_index;
 char temp;
 int indx = 0;

 /* Step through each byte in the padded_fascn. If its a 1, print a 1 */
 /* else print a 0.  Also, print a space after every 5th print so the */
 /* results will match the 5-bit groups in the PACS example.          */

 for (bit_count = 0, byte_count = 0; byte_count < 25; byte_count++) {
   temp = padded_fascn[byte_count];
   for (bit_index=0; bit_index < 8; bit_index++) {
    if (mask & temp) {/* is the most significant bit a 1? */
      putchar('1');  /* if it a 1, print a 1 */
      outputString[indx++] = '1';
      }
    else {
      putchar('0');  /* if its not a 1, it must be a 0 so print o */
      outputString[indx++] = '0';
      }
    temp <<= 1; /* shift left to prepare the next bit for testing */
    bit_count += 1;
    if ((bit_count % 5)== 0) { /* is this the 5th 1 or 0 printed? */
      putchar(' '); /* add a space between 5-bit characters */
      outputString[indx++] = ' ';
      }
    }
   } /* end for */
  outputString[239] = '\0';
  return(0);
  }


 /******************************************************************/
 /*                                                                */
 /* Compare the output string agains an expected string            */
 /*                                                                */
 /******************************************************************/

int compare_output_string( char expected_string[240] )
{
 int char_count = 0;
 while( char_count < 240 ) {
  if( outputString[char_count] != expected_string[char_count] ) {
    printf("Error encountered in output string at charater # %d\n",char_count );
    printf("Expected  %d \n", expected_string[char_count] );
    printf("and found %d \n", outputString[char_count] );
    exit(1);
    }
  char_count++;
  }
}


 /******************************************************************/
 /*                                                                */
 /* Calculate the Longitudinal Redundancy Character (checksum)     */
 /* This function is a exclusive or (XOR) of all characters. When  */
 /* the sum is taken, the parity must be calculated. To do this    */
 /* the number of 1's are counted and then divided using MOD 2     */
 /* or radix 2 division. If the result is 1, then there are an odd */
 /* number of 1's so a 0 is the least significant bit. In          */
 /* contrast, if the result is a 0, then a 1 is the parity bit and */
 /* must be the least significant bit.                             */
 /*                                                                */
 /******************************************************************/


int lrc()
{
 int  count;
 int  ones = 0;
 char checksum, temp_char = 0;

 /* add up everything using XOR (mode 2 addition) */

 for (checksum=0, count=0; count < 39; count++)
   checksum ^= expanded_fascn[count];

 /* shit the temporary working value one place to the right */

 temp_char = (checksum >> 1); /* right shift to delete parity bit */

 /* sum the number of bits */

 for (count = 0; count < 4; count++) {

  if (temp_char & 0x01)
  ones += 1; /* increment the number of ones */
  temp_char >>= 1; /* right shift */
  }

 /* See if the number of 1's is an even or odd number where */
 /* a 1 indicates odd and a 0 even                          */

  if ((ones % 2) == 1)
  checksum &= 0x1e; /* Make the least significant bit 0 */
  else
  checksum |= 0x01; /* Make the least significant bit 1 */

 /* Expand the checksum (LRC) at offset 39 */

 int checksumvalue = checksum;

 printf("LRC = %d\n",checksumvalue);

 expanded_fascn[39] = checksum;
 return(0);
}

/******************************************/
/*                                        */
/* fascn ac sc cn cs ici pi oc oi poa     */
/* Where ac is the Agency Code            */
/* sc is the System Code                  */
/* cn it the Credential Number            */
/* cs is the Credential Series            */
/* ici is the Individual Credential Issue */
/* pi is the Personal Identifier          */
/* oc is the Organizational Category      */
/* oi is the Organizational Identifier    */
/* poa is the Person/Organization         */
/*                                        */
/*  There are 9 arguments passed in the   */
/*  order listed and all are characters   */
/*                                        */
/******************************************/

char ac[4], sc[4], cn[6],cs[1], ici[1], pi[10], oc[1], oi[4], poa[1];
char expectedlrc[1];
char expected_string[240];

main(argc, argv)
int  argc;
char *argv[];
{
 int index; /* expanded_fascn pointer */
 int count; /* local count */
 int checksum;

 /* Test to see if the number of arguments passed is correct.  If its not */
 /* provide a warning message and terminate the program. Show what the    */
 /* correct call should be.                                               */

 if (argc != 12) {
  printf("Incorrect number of arguments for this function \n");
  printf("fascn ac sc cn cs ici pi oc oi poa expectedlrc\n");
  exit(1);
  }

 /* initialize */

 /* copy the strings into more meaningful nmenoics for */

  strncpy(ac, argv[1], 4);
  strncpy(sc, argv[2], 4);
  strncpy(cn, argv[3], 6);
  strncpy(cs, argv[4], 1);
  strncpy(ici,argv[5], 1);
  strncpy(pi, argv[6],10);
  strncpy(oc, argv[7], 1);
  strncpy(oi, argv[8], 4);
  strncpy(poa,argv[9], 1);
  strncpy(expectedlrc,argv[10], 1);
  strncpy(expected_string,argv[11], 240);
  expected_string[239]='\0';

 /* Expand the Agnecy Code (ac) starting at offset 1 */

 for (count=0,index=1; count<4; count++,index++)
   expanded_fascn[index] = convert_number(ac[count]);

 /* Expand the System Code (sc) starting at offset 6 */

 printf("\n"); for (count=0, index=6; count < 4; count++, index++)
   expanded_fascn[index] = convert_number(sc[count]);

 /* Expand the Credential Number starting at offset 11 */

 for (count=0, index=11; count < 6; count++, index++)
   expanded_fascn[index] = convert_number(cn[count]);

 /* Expand the Credential Series at offset 18 */

 expanded_fascn[18] = convert_number(cs[0]);

 /* Expand the Individual Credential Issue (ici) at offset 20 */

 expanded_fascn[20] = convert_number(ici[0]);

 /* Expand the Person Identifier (pi) at offset 22 */

 for (count=0, index=22; count < 10; count++, index++)
   expanded_fascn[index] = convert_number(pi[count]);

 /* Expand the Organizational Category (oc) at offset 32 */

 expanded_fascn[32] = convert_number(oc[0]);

 /* Expand the Organizational Identifier (oi) at offset 33 */

 for (count=0, index=33; count < 4; count++, index++)
   expanded_fascn[index] = convert_number(oi[count]);

 /* Expand the Person/Organization Association Category (poa) */
 /* at offset 37                                              */

 expanded_fascn[37] = convert_number(poa[0]);

 lrc();

 /* convert the 40 character expanded FASC-N to its 25-bit version */

 padd_function();

 /* print the bits to verify the results */

 print_bits();

 printf("Output String = %s\n", outputString);

 compare_output_string( expected_string );

 if( expanded_fascn[39] != expectedlrc[0] ) {
   printf("Incorrect LRC\n");
   exit(1);
   }

 exit(0);
}

