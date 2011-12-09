
/****************************************************************

When the Organizational Category is 1, then the Organizational
Identifier identifies the Government entity that issued the FASC-N. 
The complete list is specified in the National Institute of Standards and Technology 
(NIST) Special Publication 800-87 (current revision is 1). Some values are listed
below:

1200 AGRICULTURE, Department of
1300 COMMERCE, Department of
9700 DEFENSE, Department of (except military departments)
5700 AIR FORCE, Department of the (Headquarters, USAF)
2100 ARMY, Department of the (except Corps of Engineers Civil Program Financing)
1700 NAVY, Department of the
9100 EDUCATION, Department of
8900 ENERGY, Department of
7500 HEALTH AND HUMAN SERVICES, Department of
7000 HOMELAND SECURITY, Department of
8600 HOUSING AND URBAN DEVELOPMENT, Department of
1400 INTERIOR, Department of the
1500 JUSTICE, Department of
1600 LABOR, Department of
1900 STATE, Department of
6900 TRANSPORTATION, Department of
2000 TREASURY, Department of the
3600 VETERANS AFFAIRS, Department of
6800 ENVIRONMENTAL PROTECTION AGENCY
4700 GENERAL SERVICES ADMINISTRATION
8000 NATIONAL AERONAUTICS AND SPACE ADMINISTRATION
8800 NATIONAL ARCHIVES AND RECORDS ADMINISTRATION
4900 NATIONAL SCIENCE FOUNDATION
2400 OFFICE OF PERSONNEL MANAGEMENT
2800 SOCIAL SECURITY ADMINISTRATION

Dependencies:

Requires the toint() function that converts a character in the range '0' to '9' to an integer.
If the character converted is not '0' - '9' the function returns a value of 0.

*****************************************************************/

int organizational_identifier(fascn)

	char fascn[40];
{
	int temp;
	temp = toint(fascn[33]) * 1000;
	temp += toint(fascn[34]) * 100;
	temp += toint(fascn[35]) * 10;
	temp += toint(fascn[36]);
	return(temp);
}