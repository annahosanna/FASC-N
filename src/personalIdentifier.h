
/***************************************************************************

As noted in the Technical Implementation Guidance:
Smart Card Enabled Physical Access Control Systems

PERSON IDENTIFIER:

Numeric Code used by the identity source to uniquely identify the token
carrier. (e.g. DoD EDI PN ID, TWIC credential number, NASA UUPIC)

Note: the DoD and VA use the EDI-PI to uniquely identify people.

Users of string functions should ensure the proper termination of the string function.

***************************************************************************/

#ifndef personalIdentifier_h
#define personalIdentifier_h

int personalIdentifier( char fascn[40], char PI[10] );

#endif
