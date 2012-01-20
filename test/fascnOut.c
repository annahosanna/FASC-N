

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ss 0x1a /* 0001 1010 */
#define fs 0x16 /* 0001 0110 */
#define es 0x1f /* 0001 1111 */

int debug_count = 0;
char * referencefile;

/*************************************************

The convert number uses the PACS table as a
conversion function.

Note: The NIST SP 800-87 Rev 1 allows agency codes of 'A' to 'F' Three
of these binary coded decimals (BCDs) are used for other purposes
Start Sentinel BCD 'D'
Field Separator BCD 'B'
End Sentinel BCD 'F'
If we allowed these, some of the physical access control system (PACS)
devices would not operate properly. To address this ambiguity, any value
passed in the 'A' to 'F' range is converted to a value '0'

*************************************************/

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
  default: return_value = 0x01; /* if its a BCD 'A' to 'F' make it a zero */
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


  /************************************************************/
  /*                                                          */
  /* The print_fascn will ask for a file name and place a     */
  /* binary FASN-N in there                                   */
  /*                                                          */
  /************************************************************/

int print_fascn()

{
int byteCount;


  FILE *fp;
  if ((fp = fopen("fascn.dat", "w")) == NULL) {
    return(1);
    }

  for(byteCount=0; byteCount<25; byteCount++) {
   fputc(padded_fascn[byteCount], fp);
   }

  fclose(fp);
  return(0);
}


  /************************************************************/
  /*                                                          */
  /* The compare_with_expected_fascn() will compare the       */
  /* padded_fascn with one provided by an external file.      */
  /*                                                          */
  /************************************************************/

int compare_with_expected_fascn()

{
int byteCount;
char inputChar;


  FILE *fp;
  if ((fp = fopen(referencefile, "rb")) == NULL) {
    printf("Error opening file %s\n",referencefile);
    exit(1);
    }

  for(byteCount=0; byteCount<25; byteCount++) {
    inputChar = fgetc(fp);
    if( padded_fascn[byteCount] != inputChar ) {
      printf("Error in padded_fascn byte %d\n",byteCount);
      printf("Expected  %d \n", inputChar );
      printf("and found %d \n", padded_fascn[byteCount] );
      exit(1);
      }
    }

  fclose(fp);

  printf("Success in comparison with reference file\n");

  return(0);
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

 expanded_fascn[39] = checksum;
 return(0);
}

/******************************************/
/*                                        */
/* fascnOut ac sc cn cs ici pi oc oi poa  */
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


int main(argc, argv)
int  argc;
char *argv[];
{
 int index; /* expanded_fascn pointer */
 int count; /* local count */
 int checksum;

 /* Test to see if the number of arguments passed is correct.  If its not */
 /* provide a warning message and terminate the program. Show what the    */
 /* correct call should be.                                               */

 if (argc != 11) {
  printf("Incorrect number of arguments for this function \n");
  printf("fascnOut ac sc cn cs ici pi oc oi poa referencefile\n");
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
  referencefile = argv[10];

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

 print_fascn(); /* binary print */

 compare_with_expected_fascn();

 return(0);
}

