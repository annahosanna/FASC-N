/*****************************************************************************

With the newer 64-bit computers and associated operating system, using 64-bit integers
should be more efficient than comparing character strings. The PI_number() takes the
10-digit Personal Identifier and converts it to a number. Note, the DoD and VA use an
EDI-PI that is a 9-gigit number with a concatenated checksum. Although the number only has 9-digits
of meaningful information, applications might have been expanded to accommodate 10-digit
numbers.

*****************************************************************************/
#ifndef PINumber_h
#define PINumber_h

long long PI_number( char fascn[40] );

#endif
