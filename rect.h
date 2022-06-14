#ifndef __RECT_H_INCL
#define __RECT_H_INCL

#include "cclass.h"
#include <stdio.h>

// the main structure of your class
struct __Rect_t{
	int l;
	int b;
};

// initialization / creation of cclass
void __Rect_init(void* __object)
{
	struct __Rect_t* self = (struct __Rect_t*)__object;
	self->l = 0;
	self->b = 0;
}

// constructor of cclass
void __Rect_construct(void* __object, const char* cname, va_list va)
{
	struct __Rect_t* self = (struct __Rect_t*)__object;

	if (cname=="lb")
	{
		int x = va_arg(va,int), y = va_arg(va,int);
		self->l = x;
		self->b = y;
	}
}
// method of cclass [ all methods to be kept here and must return rval i.e return value]
// to keep value in rval pack it using rval.val = rv_func.pack(&var,sizeof(var));

rval __Rect_method(void* obj, const char* mname, ...)
{
	va_list va;
	va_start(va,mname);
	// must include if want to give inheritance
	if(mname=="size")
	{
		rval v = {NULL,'u'};
		size_t s = sizeof(struct __Rect_t);
		v.val = rv_func.pack(&s,sizeof(s));
		return v;
	}

	struct __Rect_t* self = (struct __Rect_t*)obj;

	if (mname=="print")
	{
		rval rt = {NULL,'0'};
		printf("RectObj(length=%d,breadth=%d)\n",self->l,self->b);
		return rt;
	}
	else if(mname=="area")
	{
		int area = self->l*self->b;
		// i is for int
		rval rt = {NULL,'i'};
		rt.val = rv_func.pack(&area,sizeof(area));
		return rt;
	}
	else if(mname=="getl")
	{
		rval rt = {NULL,'i'};
		int p = self->l;
		rt.val = rv_func.pack(&p,sizeof(p));
		return rt;
	}
	else if(mname=="getb")
	{
		rval rt = {NULL,'i'};
		int p = self->b;
		rt.val = rv_func.pack(&p,sizeof(p));
		return rt;
	}
	else if(mname=="setlb")
	{
		self->l = va_arg(va,int);
		self->b = va_arg(va,int);
		rval rt = {NULL,'0'};
		return rt;
	}

	va_end(va);
	rval rt = {NULL,'0'};
	return rt;
}
// pack into rect cclass
cclass rect = {sizeof(struct __Rect_t),__Rect_init,__Rect_construct,__Rect_method};

#endif