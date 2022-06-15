#ifndef _SQUARE_H_INCL
#define _SQUARE_H_INCL
// inheriting from rect to square
#include "cclass.h"
#include "rect.h"

int square_construct(c_object obj, const char* nm, arg_typ args, void* _super)
{
	class* super = (class*)_super;
	if (nm=="setside")
	{
		int side = arg_get(args, int);
		internal_method(super, obj, nm, side, side);
		return 1;
	}
	return 0;
}

mval square_method(c_object obj, const char* nm, arg_typ args, void* _super)
{
	mval ok = {NULL,200};
	mval not_found = {NULL,404};
	class * super = (class*)_super;
	if (nm=="print")
	{
		mval l = internal_method(super, obj, "getl");
		printf("SquareObj(side=%d)\n",mvf.get_int(l));
		l = mvf.done(l);
		return ok;
	}
	return not_found;
}
class square = {0, NULL, square_construct, square_method, &rect};

#endif