#ifndef _RECT_H_INCL
#define _RECT_H_INCL

// include class.h
#include "cclass.h"

// variable of your class to be kept here
// use names like __classname_type to make it look internal and it is internal of course
struct rect_t
{
	int l;
	int b;
};

// intitialization of object
// use names like __classname_func to make it look internal and is internal of course
void rect_init(c_object obj, void* super)
{
	// make up the this variable / object [ this is usually needed in all functions ]
	struct rect_t* this = (struct rect_t*)obj;
	
	// use this as in c++ class [ somewhat like c++ from here]
	this->l = 0;
	this->b = 0;
}

// construction of object
// use names like __classname_func to make it look internal and is internal of course
// we don't need super but it is to be included in functions
// to support inheritance if we don't need we just dont use
int rect_construct(c_object obj, const char* nm, arg_typ args, void* super)
{
	// make up the this variable / object [ this is usually needed in all functions ]
	struct rect_t* this = (struct rect_t*)obj;

	// construct methods [ lb is lengthBreadth]
	if (nm=="lb")
	{
		// pretty much like c++ this
		this->l = arg_get(args,int);
		this->b = arg_get(args,int);
		// correctly constructed!
		return 1;
	}
	// not correctly constructed
	return 0;
}

/*	methods of object which can return multiple variables
	you have a space of total of 0 - 4294967295 numbers
	in normal systems to indicate different types to return
default are :-
// normal states when no return
200 :- NULL [ no return but ok state]
400 :- NULL [ no return but not found state ]

// normal state when returned
0 :- int
1 :- unsigned int
2 :- char
3 :- char*
4 :- float
5 :- double
6 :- long
7 :- unsigned long
8 :- long long
9 :- unsigned long long
// note: you need to use mvf.getType(varName) for getting the variable for Type type.
// note: you need to use mvf.done(varName) after using mval
*/
mval rect_method(c_object obj, const char* nm, arg_typ args, void* super)
{
	// make up the `this` variable / object [ `this` is usually needed in all functions ]
	struct rect_t* this = (struct rect_t*)obj;

	mval ok = {NULL,200};
	mval not_found = {NULL,404};
	
	// methods [ print to print the object ]
	if (nm=="print")
	{
		// pretty much like c++ member var access when using `this`
		printf("RectObj(l=%d,b=%d)\n",this->l,this->b);
		return ok;
	}else if (nm=="setlb"){
		// pretty much like c++ member var access
		this->l = arg_get(args,int);
		this->b = arg_get(args,int);
		return ok;
	}else if (nm=="area"){
		// to return you need to do this
		// mval var = {NULL, (2 for int and 3 for unsigned int ...) }
		mval rt = {NULL,2};
		
		// calculate inside a variable
		int area = this->l*this->b;
		
		// pack the variable into rt.val [ this causes hard pack so after using
		// rvf.done(varName) is mandatory in main function ]
		rt.val = mvf.pack(&area,sizeof(area));
		
		// send rt as response
		return rt;
	}

	// method not found! else it would already return ok or smth else
	return not_found;
}

// pack all things in rect class [ and make sure the inheritance is null! ]
class rect = {sizeof(struct rect_t), rect_init, rect_construct, rect_method, NULL};

#endif