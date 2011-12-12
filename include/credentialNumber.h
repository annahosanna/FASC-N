/****************************************************************************

As noted in the Technical Implementation Guidance:
Smart Card Enabled Physical Access Control Systems

CREDENTIAL NUMBER

Encoded by the issuing agency. For a given system no duplicate
numbers are active

The value is returned as a long integer (32-bits in length)

As noted in the Technical Implementation Guidance:
Smart Card Enabled Physical Access Control Systems

Credential Number

In order to insure uniqueness of the fully qualified number assignment the Credential
Number assignment is the responsibility of the CIO for the organization referenced by
the Agency Code. Under the assigned Agency Code the CIO may not delegate the
responsibility for Agency policy ensuring unique fully qualified number assignment to
individuals. The authority to assign Credential Numbers may be delegated by the CIO.

Agency CIOs are responsible for insuring non-overlapping Credential Numbers are
issued for all interoperable systems issuing FASC-N codes within their Agency.

The combination of an Agency Code, System Code and Credential Number is a fully
qualified number that is uniquely assigned to a single individual.

****************************************************************************/
#ifndef credentialNumber_h
#define credentialNumber_h

long int credential_number( char fascn[40] );

#endif
