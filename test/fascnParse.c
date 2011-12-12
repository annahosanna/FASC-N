

#include <stdio.h>

#include "toint.h"
#include "convertCharacter.h"
#include "expandFascn.h"
#include "personalIdentifier.h" /* text return of PI */
#include "PINumber.h" /* Number return of PI */
#include "agencyCode.h"
#include "systemCode.h"
#include "credentialNumber.h"
#include "credentialSeries.h"
#include "individualCredential.h"
#include "organizationalCategory.h" /* Is NIST SP 800-87 used? */
#include "organizationalIdentifier.h" /* Agency issuing FASC-N */
#include "poa.h"
#include "errorCode.h"

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

/******************************************

This program is a sample of pulling in each of the software programs. Note, the definitions
provided at the top along with the data structures. Note, a function to recalculate the
longitudinal redundancy character (LRC) was note performed. If needed, the fascn.c test fixture
includes a calculating function. Programmers are expected to define their own error value
with the proper programming scope. A default of 'Z' is used in this test.

/******************************************/

main(argc, argv)
int  argc;
char *argv[];
{

 read_fascn(); /* function to load in the FASC-N from a file */

 expand_fascn(padded_fascn, expanded_fascn);
 /* The personalIdentifier sets PI to the character array of the PI */
 personalIdentifier(expanded_fascn, PI);
 printf("The Personal Identifier is: %s\n",PI);
 printf("The PI as a number is: %lld\n",PI_number(expanded_fascn));
 printf("The Agency Code is: %d\n", agency_code(expanded_fascn));
  printf("The System Code is: %d\n", system_code(expanded_fascn));
  printf("The credential number is: %ld\n", credential_number(expanded_fascn));
  printf("The credential series is: %d\n", credential_series(expanded_fascn));
  printf("The individual credential issue is: %d\n", individual_credential_issue(expanded_fascn));
  printf("The Organizational Category is: %d\n", organizational_category(expanded_fascn));
  printf("The Organizational Identifier is: %d\n", organizational_identifier(expanded_fascn));
  printf("The Person/Organization Association Category is: %d\n", person_organization_association(expanded_fascn));
}

