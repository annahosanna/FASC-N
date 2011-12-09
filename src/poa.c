/************************************************************************

As noted in the Technical Implementation Guidance:
Smart Card Enabled Physical Access Control Systems

PERSON/ORGANIZATION ASSOCIATION CATEGORY
1 – Employee
2 – Civil
3 – Executive Staff
4 – Uniformed Service
5 – Contractor
6 – Organizational Affiliate
7 – Organizational Beneficiary


Dependencies:

Requires the toint() function that converts a character in the range '0' to '9' to an integer.
If the character converted is not '0' - '9' the function returns a value of 0.

************************************************************************/



int person_organization_association(fascn)
  char fascn[40];
{
  int temp;
  temp = toint(fascn[37]);
  return(temp);
}
