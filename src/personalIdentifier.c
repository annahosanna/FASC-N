
/***************************************************************************

As noted in the Technical Implementation Guidance:
Smart Card Enabled Physical Access Control Systems

PERSON IDENTIFIER:

Numeric Code used by the identity source to uniquely identify the token
carrier. (e.g. DoD EDI PN ID, TWIC credential number, NASA UUPIC)

Note: the DoD and VA use the EDI-PI to uniquely identify people.

Users of string functions should ensure the proper termination of the string function.

***************************************************************************/


int personalIdentifier(fascn, PI)
  char fascn[40], PI[10];
{
  int index;
  for (index=0; index<10; index++)
    PI[index] = fascn[22+index];
  return(0);
}
