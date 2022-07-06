#include "rect.h"
#include <stdio.h>

int main()
{
	object o = construct(rect, "lb", 20, 10);

	multi_type val = o.method(o, "getArea");

	printf("The area is: ");
	mtype_print(val);
	printf("\n");

	o = o.delete(o);
	return 0;
}