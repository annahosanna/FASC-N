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


Dependencies:

Requires the toint() function that converts a character in the range '0' to '9' to an integer.
If the character converted is not '0' - '9' the function returns a value of 0.

****************************************************************************/

long int credential_number(fascn)
	char fascn[40];
{
	long int temp;
	temp = toint(fascn[11]) * 100000;
	temp += toint(fascn[12]) * 10000;
	temp += toint(fascn[13]) * 1000;
	temp += toint(fascn[14]) * 100;
	temp += toint(fascn[15]) * 10;
	temp += toint(fascn[16]);
	return(temp);
}
