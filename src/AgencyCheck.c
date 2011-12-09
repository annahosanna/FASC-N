

#include <stdio.h>

#define error 'Z' /* The error return value */
char padded_fascn[25]; /* This is the 25-byte FASC-N format on the CAC/PIV card */
char expanded_fascn[40]; /* The 40-byte expanded FASC-N format */
char PI[10]; /* A text return of the personal identifier. Note, programmers must check array bounds */

/*************************************************

read_fascn() will read in the binary FASC-N from a default file fascn.dat
While this is adequate for testing, a different delivery is expected in practice.

*************************************************/

int read_fascn()
{
 int byteCount;
 FILE *fp;
 if ((fp = fopen("fascn.dat", "r")) == NULL)
   return(1);
 for(byteCount=0; byteCount<25; byteCount++)
   padded_fascn[byteCount] = fgetc(fp);
 fclose(fp);
 return(0);
}

#include "toint.c"
#include "convertCharacter.c"
#include "expandFascn.c"
#include "PINumber.c" /* Number return of PI */
#include "organizationalCategory.c" /* Is NIST SP 800-87 used? */
#include "organizationalIdentifier.c" /* Agency issuing FASC-N */


/******************************************

This program is a sample of using six of the C functions to determine if a person
is part of the DoD or VA and then  what their ID number

/******************************************/

main(argc, argv)
int  argc;
char *argv[];
{
 int agency;
 read_fascn(); /* function to load in the FASC-N from a file */
 expand_fascn(padded_fascn, expanded_fascn);
 if(organizational_category(expanded_fascn) == 1)
 {   agency = organizational_identifier(expanded_fascn);
     agency -= agency % 100; /* truncate to department number */
     printf("Agency = %d\n", agency);
   switch(agency){
   case 1700: {
     printf("Navy identified\n");
     break; }
   case 2100: {
     printf("Army identified\n");
     break; }
   case 3600: {
     printf("VA identified\n");
     break; }
   case 5700: {
     printf("Air Force identified\n");
     break; }
   case 9700: {
     printf("DoD identified\n");
     break; }
   }
 }
 printf("The ID Number is: %lld\n",PI_number(expanded_fascn));

}

