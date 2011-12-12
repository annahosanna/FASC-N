
/************************************************************************

As noted in the Technical Implementation Guidance:
Smart Card Enabled Physical Access Control Systems

SYSTEM CODE

Identifies the system the card is enrolled in and is unique for each site

In order to ensure uniqueness of the fully qualified number assignment the System Code
number assignment is the responsibility of the CIO for the organization referenced by the
Agency Code. The authority to assign a single and blocks of System Codes may be
delegated by the CIO.

Agency CIOs are responsible for ensuring non-overlapping System Codes are issued for
all interoperable systems issuing SEIWG-012 credential number or FASC-N codes
within their Agency.

The combination of each Agency Code and System Code permit one million unique fully
qualified numbers. If a particular issuing system requires more than one million
credentials issued then that system would require an additional system code assigned
corresponding to each million credentials that will be issued by that system.

************************************************************************/

#ifndef systemCode_h
#define systemCode_h

int system_code( char fascn[40] );

#endif
