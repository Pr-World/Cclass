#ifndef _CCLASS_H_INCL

#define _CCLASS_H_INCL
#define arg_get va_arg
#define arg_typ va_list
#define arg_init va_start
#define arg_end va_end
#define _OOP_MEM_CHECK if(_TEST==NULL){printf("%s\n","Memory error occured! exitting");exit(10);}

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

// output type used to output multi type var
typedef struct mval
{
	void* val;
	unsigned int type;
} mval;

typedef void* c_object;

typedef struct class
{
	size_t size;
	void(*init)(c_object, void*);
	// returns state if construct happened correctly
	int (*construct)(c_object, const char*, arg_typ, void*);
	mval (*method)(c_object, const char*, arg_typ, void*);
	struct class* __inherited;
} class;

typedef struct object{
	c_object self;
	mval(*method)(c_object,const char*, arg_typ, void*);
	struct class* __inherited;
}object;

object new(class c, ...)
{
	arg_typ va;
	arg_init(va,c);
	void * _TEST;

	if (c.size==0 && c.__inherited->size!=0)
		_TEST = malloc(c.__inherited->size);
	else
		_TEST = malloc(c.size);
	// checks for memory
	_OOP_MEM_CHECK

	// class initialize to o
	object o = {_TEST, c.method};
	char* p = arg_get(va,char*);
	if(p=="construct"){
		if (c.construct==NULL)
			c.__inherited->construct(o.self,arg_get(va,char*),va,c.__inherited->__inherited);
		else
			c.construct(o.self,arg_get(va,char*),va,c.__inherited);
	}else{
		if (c.init==NULL)
			c.__inherited->init(o.self,c.__inherited->__inherited);
		else
			c.init(o.self,c.__inherited);
	}
	o.__inherited = c.__inherited;
	arg_end(va);
	return o;
}

object construct(class c, const char* nm, ...)
{
	arg_typ va;
	arg_init(va,nm);
	
	void* _TEST = malloc(c.size);;
	// checks for memory
	_OOP_MEM_CHECK
	object o = {_TEST, c.method};
	if (c.construct==NULL){
		c.__inherited->construct(o.self, nm, va, c.__inherited->__inherited);
	}else{
		int f = c.construct(o.self, nm, va, c.__inherited);
		if (f==0 && c.__inherited!=NULL)
			c.__inherited->construct(o.self, nm, va, c.__inherited->__inherited);
	}
	o.__inherited = c.__inherited;
	arg_end(va);
	return o;
}

object delete(object o)
{
	free(o.self);
	object a = {NULL,NULL};
	return a;
}

mval method(object o, char* nm, ...)
{
	arg_typ va;
	arg_init(va,nm);
	mval b;
	if (o.method==NULL){
		o.__inherited->method(o.self,nm,va,o.__inherited->__inherited);
	}else{
		b = o.method(o.self,nm,va, o.__inherited);
		if (b.type==404 && o.__inherited != NULL)
			b = o.__inherited->method(o.self,nm,va,o.__inherited->__inherited);
	}
	arg_end(va);
	return b;
}

mval internal_method(class* c, c_object o, const char* nm, ...)
{

	arg_typ va;
	arg_init(va,nm);
	mval b;
	if (c->method==NULL){
		c->__inherited->method(o,nm,va,c->__inherited->__inherited);
	}else{
		b = c->method(o,nm,va, c->__inherited);
		if (b.type==404 && c->__inherited != NULL)
			b = c->__inherited->method(o,nm,va,c->__inherited->__inherited);
	}
	arg_end(va);
	return b;
}

void* _mvfunc_pack(void* ptr, size_t s)
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

mval _mvfunc_done(mval a)
{
	free(a.val);
	mval b = {NULL,200};
	return b;
}

int _mvfunc_getint(mval r){
	return ((int*)(r.val))[0];
}

char _mvfunc_getchr(mval r){
	return ((char*)(r.val))[0];
}

char* _mvfunc_getstr(mval r){
	return (char*)(r.val);
}

double _mvfunc_getdbl(mval r){
	return ((double*)(r.val))[0];
}

float _mvfunc_getflt(mval r){
	return ((float*)(r.val))[0];
}

/* -- UNCOMMENT TO ADD oop.new etc functions
typedef struct __OOP_TYPE
{
	object(*new)(class);
	object(*construct)(class,const char*,int,...);
	object(*delete)(object);
} __OOP_TYPE;

// pack to oop
__OOP_TYPE oop = {
	new,construct,delete
};
*/


// mval function type
typedef struct __MVAL_FNC_TYPE
{
	void*(*pack)(void*,size_t);
	mval(*done)(mval);
	int(*get_int)(mval);
	char(*get_chr)(mval);
	char*(*get_str)(mval);
	double(*get_dbl)(mval);
	float(*get_flt)(mval);
} __MVAL_FNC_TYPE;

// pack mval function to mvf
__MVAL_FNC_TYPE mvf = {
	_mvfunc_pack,_mvfunc_done,_mvfunc_getint,_mvfunc_getchr,_mvfunc_getstr,
	_mvfunc_getdbl,_mvfunc_getflt
};

#endif