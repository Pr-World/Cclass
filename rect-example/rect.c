#include "rect.h"
#include <stdio.h>
#include <string.h>

typedef struct
{
	int l, b;
} Rect_Struct;

// for custom use
int isEq ( const char* a, const char* b)
{
	return strcmp(a,b)==0;
}

void Rect_Create ( actual_obj obj, cclass* super )
{
	// warn bypass
	warn_bypass(super);

	// makeup this
	Rect_Struct* this = (Rect_Struct* ) obj;

	this -> l = 0;
	this -> b = 0;
}

void Rect_Construct ( actual_obj obj, const char* type, va_list args, cclass* super )
{
	// warn bypass
	warn_bypass(super);

	// makeup this
	Rect_Struct* this = (Rect_Struct* ) obj;

	if( isEq(type, "lb") )
	{
		this -> l = va_arg(args, int);
		this -> b = va_arg(args, int);
	}
	else
	{
		Rect_Create(obj, super);
	}
}

multi_type Rect_Method ( actual_obj obj, const char* name, va_list args, cclass* super )
{
	// warn bypass
	warn_bypass(super);
	warn_bypass(&args);

	// makeup this
	Rect_Struct* this = (Rect_Struct* ) obj;

	multi_type toRet = {400, NULL};

	if( isEq(name, "print") )
	{
		printf("Rect(length=%d, breadth=%d)\n", this -> l, this -> b);
		return toRet;
	}
	else if( isEq(name, "getArea") )
	{
		// calculate area
		int area = this -> l * this -> b;

		// integer type
		toRet.type = 300;
		toRet.value = &area;

		return toRet;
	}
	else if( isEq(name, "getPerimeter") )
	{
		// calculate perimeter
		int p = 2 * ( this -> l + this -> b );

		// integer type
		toRet.type = 300;
		toRet.value = &p;

		return toRet;
	}
	else
	{
		toRet.type = 401;
		return toRet;
	}
}

size_t Rect_Size = sizeof(Rect_Struct);

cclass rect = {
	"Rect",
	&Rect_Size,
	Rect_Create,
	Rect_Construct,
	Rect_Method,
	NULL, NULL // no delete function or super class
};