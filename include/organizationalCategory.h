/****************************************************************

The following is taken from the Technical Implementation Guidance:
Smart Card Enabled Physical Access Control Systems Version 2.3

ORGANIZATIONAL IDENTIFIER
OC=1 – NIST SP800-87 Agency Code
OC=2 – State Code
OC=3 – Company Code
OC=4 – Numeric Country Code

For DoD, VA, and other federal users, a value returned of 1 indicated the
4 character Organizational Identifier will contain the issuing Agency's code
as specified in the National Institute of Standards & Technology (NIST)
Special Publication 800-87 (current revision is 1)

*****************************************************************/
#ifndef organizationalCategory_h
#define organizationalCategory_h

int organizational_category( char fascn[40] );

#endif
