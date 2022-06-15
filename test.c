#include <stdio.h>
#include <stdlib.h>
#include "rect.h"

int main(int argc, char const *argv[])
{
	// create a new rect
	object o = new(rect); // can also use [ = construct(rect, "lb", lengthVal, breadthVal);]
	
	// print without doing anything [use method print]
	method(o,"print");
	// assign values l=10, b=20 [use method setlb (set length breadth)]
	method(o,"setlb",10,20);
	// print the object again [use method print defined in class]
	method(o,"print");

	mval rt = method(o,"area");
	printf("Area : %d\n", mvf.get_int(rt));
	mvf.done(rt);

	delete(o);
	return 0;
}