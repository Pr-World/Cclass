#include <stdio.h>
#include <stdlib.h>
#include "rect.h"

int main(int argc, char const *argv[])
{
	object o = new(rect);
	rect.method(o.self,"print");
	delete(o);
	return 0;
}