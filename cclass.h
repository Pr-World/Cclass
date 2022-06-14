#ifndef _CCLASS_H_INCL
#define _CCLASS_H_INCL

#define _OOP_MEM_CHECK if(_TEST==NULL){printf("%s\n","Memory error occured! exitting");exit(10);}

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

// output type used to output multi type var
typedef struct rval
{
	void* val;
	char type;
} rval;

typedef struct cclass
{
	size_t size;
	void(*init)(void*);
	void(*construct)(void*,const char*,va_list);
	rval(*method)(void*,const char*,...);
} cclass;

typedef struct object
{
	cclass* parent;
	void* self;
} object;

object __oop_create(cclass c)
{
	object o;
	o.parent = &c;
	o.self = malloc(o.parent->size);
	
	void* _TEST = o.self;
	_OOP_MEM_CHECK

	o.parent->init(o.self);
	return o;
}

object __oop_construct(cclass c, const char* nm, ...)
{
	va_list va;
	va_start(va,nm);
	
	object o;
	o.parent = &c;
	o.self = malloc(o.parent->size);

	void* _TEST = o.self;
	_OOP_MEM_CHECK

	o.parent->construct(o.self, nm, va);
	va_end(va);
	return o;
}

object __oop_delete(object o)
{
	free(o.self);
}

void* _rvfunc_pack(void* ptr, size_t s)
{
	void* _TEST = malloc(s);
	_OOP_MEM_CHECK
	size_t i;
	for (i = 0; i < s; ++i)
	{
		((char*)_TEST)[i]=((char*)ptr)[i];
	}
	return _TEST;
}

void _rvfunc_done(rval a)
{
	free(a.val);
}

int _rvfunc_getint(rval r){
	return ((int*)(r.val))[0];
}

char _rvfunc_getchr(rval r){
	return ((char*)(r.val))[0];
}

char* _rvfunc_getstr(rval r){
	return (char*)(r.val);
}

double _rvfunc_getdbl(rval r){
	return ((double*)(r.val))[0];
}

float _rvfunc_getflt(rval r){
	return ((float*)(r.val))[0];
}

/* -- UNCOMMENT TO ADD oop.create etc functions
typedef struct __OOP_TYPE
{
	object(*create)(cclass);
	object(*construct)(cclass,const char*,int,...);
	object(*delete)(object);
} __OOP_TYPE;

// pack to oop
__OOP_TYPE oop = {
	__oop_create,__oop_construct,__oop_delete
};
*/


// rval function type
typedef struct __RVAL_FNC_TYPE
{
	void*(*pack)(void*,size_t);
	void(*done)(rval);
	int(*get_int)(rval);
	char(*get_chr)(rval);
	char*(*get_str)(rval);
	double(*get_dbl)(rval);
	float(*get_flt)(rval);
} __RVAL_FNC_TYPE;

// pack rval function to rv_func
__RVAL_FNC_TYPE rv_func = {
	_rvfunc_pack,_rvfunc_done,_rvfunc_getint,_rvfunc_getchr,_rvfunc_getstr,
	_rvfunc_getdbl,_rvfunc_getflt
};

// direct functions!
object(*new)(cclass)=__oop_create;
object(*construct)(cclass,const char*, ...)=__oop_construct;
object(*delete)(object)=__oop_delete;

#endif