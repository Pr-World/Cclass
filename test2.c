#include <stdio.h>
#include <stdarg.h>
void dothis(va_list va)
{
	printf("%s !!\n",va_arg(va,char*));
}

void doa(int a, ...)
{
	int i;
	va_list va;
	va_start(va, a);
	a = (a<0) ? -a : a;
	for (i=0; i<a; i++)
	{
		dothis(va);
	}
	va_end(va);
}

int main(int argc, char const *argv[])
{
	
}