/************************************************************************

As noted in the Technical Implementation Guidance:
Smart Card Enabled Physical Access Control Systems

INDIVIDUAL CREDENTIAL ISSUE (CREDENTIAL CODE)
Recommend coding as a “1” always


Dependencies:

Requires the toint() function that converts a character in the range '0' to '9' to an integer.
If the character converted is not '0' - '9' the function returns a value of 0.

************************************************************************/


int individual_credential_issue(fascn)
	char fascn[40];
{
	int temp;
	temp = toint(fascn[20]);
	return(temp);
}
