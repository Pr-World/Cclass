#include <stdio.h>
#include <stdlib.h>

#include "person.h"

int main()
{
	object o = construct(person, "NameAgeGender", "Prakash Niroula", 16, 'M');
	
	o.method(o, "print");
	
	o = o.delete(o);
	return 0;
}