#include <stdio.h>
#include <stdlib.h>
#include "rect.h"

int main(int argc, char const *argv[])
{
	object o = construct(rect,"lb",10,20);
	
	rval a = o.method(o.self,"getl");
	printf("%d is the length!\n", rv_func.get_int(a));
	rv_func.done(a);

	delete(o);
	return 0;
}