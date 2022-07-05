#include "rect.h"
#include <stdio.h>

int main()
{
	object o = construct(rect, "lb", 20, 10);

	o.method(o, "print");

	o = o.delete(o);
	return 0;
}