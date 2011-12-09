/*****************************************************************************

With the newer 64-bit computers and associated operating system, using 64-bit integers
should be more efficient than comparing character strings. The PI_number() takes the 
10-digit Personal Identifier and converts it to a number. Note, the DoD and VA use an
EDI-PI that is a 9-gigit number with a concatenated checksum. Although the number only has 9-digits
of meaningful information, applications might have been expanded to accommodate 10-digit 
numbers.


Dependencies:

Requires the toint() function that converts a character in the range '0' to '9' to an integer.
If the character converted is not '0' - '9' the function returns a value of 0.

*****************************************************************************/

long long PI_number(fascn)
	char fascn[40];
{
	int index;
	long long PI;
	PI  = ((long long)toint(fascn[22])*1000000000);
	PI += ((long long)toint(fascn[23])*100000000);
	PI += ((long long)toint(fascn[24])*10000000);
	PI += ((long long)toint(fascn[25])*1000000);
	PI += ((long long)toint(fascn[26])*100000);
	PI += ((long long)toint(fascn[27])*10000);
	PI += ((long long)toint(fascn[28])*1000);
	PI += ((long long)toint(fascn[29])*100);
	PI += ((long long)toint(fascn[30])*10);
	PI += ((long long)toint(fascn[31]));
	return(PI);
}
