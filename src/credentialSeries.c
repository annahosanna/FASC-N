/************************************************************************

As noted in the Technical Implementation Guidance:
Smart Card Enabled Physical Access Control Systems

CREDENTIAL SERIES (SERIES CODE)
Field is available to reflect major system changes


Dependencies:

Requires the toint() function that converts a character in the range '0' to '9' to an integer.
If the character converted is not '0' - '9' the function returns a value of 0.

************************************************************************/


int credential_series(fascn)
	char fascn[40];
{
	int temp;
	temp = toint(fascn[18]);
	return(temp);
}