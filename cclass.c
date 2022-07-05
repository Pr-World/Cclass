#include "cclass.h"
#include <stdio.h>

// ---------------- < Mem allocate checker > -------------------

void cclass_check_memory ( void* obj )
{
	if ( obj==NULL )
	{
		printf("\nCclass Error [fatal] :\n Couldn't allocate memory for class, Exitting ...\n");
		exit(100);
	}
}

void cclass_check_function ( void *f, const char* class_name, const char* message )
{
	if ( f == NULL )
	{
		printf("\nCclass Error [fatal] :\n");
		printf("%s: %s, Exitting ...\n",class_name, message);
		exit(100);
	}
}

// ---------------- < / Mem allocate checker > ------------------

// ---------------- < Object Functions > --------------------

// internal delete function to be pointed for external delete function of object
// so accessible only through object.delete()
object cclass_internal_delete ( object obj )
{
	if(obj.__internal_delete!=NULL)
		obj.__internal_delete(obj.self, obj.__super);

	// free the memory

	if(obj.self!=NULL)
		free(obj.self);

	// point it's method and inheritance to null

	obj.__internal_method = NULL;
	obj.__super = NULL;
	obj.size = 0;

	// return the object
	return obj;
}

// internal method function to be pointed for external method function of object
// so accessible only through object.method()
multi_type cclass_internal_method ( object obj, const char* method_name, ... )
{
	va_list va;
	va_start(va, method_name);

	multi_type return_val = obj.__internal_method(obj.self, method_name, va, obj.__super);

	va_end(va);
	
	return return_val;
}

// public new function for creation of object
object new( cclass class )
{
	object o;

	// first, make sure that the class has a create function
	cclass_check_function(class.create, class.name, "doesn't have a create function");
	
	// allocate memory based on given size of class and make the object's size
	// to be the allocated size
	o.self = malloc(* class.size);
	o.size = * class.size;

	// check for allocated memory
	cclass_check_memory(o.self);

	// first, make sure that the class has a method function
	cclass_check_function(class.method, class.name, "doesn't have a method function");

	// make functions available [ internally used ]
	o.__internal_method = class.method;
	o.__super = class.super;

	// make functions available [ externally used in main program ]
	o.method = cclass_internal_method;
	o.delete = cclass_internal_delete;
	
	// calling the create function of that class to initialize the object
	class.create(o.self, class.super);

	return o;
}

// public construct function for construction of object
object construct ( cclass class, const char* type, ... )
{
	// using varargs for accepting any number of arguments to supply to constructor
	// of class
	va_list va;
	va_start(va, type);

	object o;

	// first, make sure that the class has a construct function
	cclass_check_function(class.construct, class.name, "doesn't have a construct function");

	// allocate memory based on given size of class
	// also made the object's size to be the allocated size
	o.self = malloc(* class.size);
	o.size = * class.size;

	// check for allocated memory
	cclass_check_memory(o.self);
	
	// first, make sure that the class has a method function
	cclass_check_function(class.method, class.name, "doesn't have a method function");

	// make functions available [ internally used ]
	o.__internal_method = class.method;
	o.__super = class.super;

	// make functions available [ externally used ]
	o.method = cclass_internal_method;
	o.delete = cclass_internal_delete;

	// calling the construct function of class
	class.construct(o.self, type, va, class.super);

	va_end(va);

	return o;
}

// ------------------ < / Object Functions > ------------------

// ------------------- < Multi Type Functions > -----------------

// check functions!

bool mtype_is_null ( multi_type val )
{
	return val.type == 400;
}

bool mtype_is_err ( multi_type val )
{
	return val.type <= 450 && val.type >= 400;
}

bool mtype_is_int ( multi_type val )
{
	return val.type == 300;
}

bool mtype_isUnsgined_int ( multi_type val )
{
	return val.type == 301;
}

bool mtype_is_long ( multi_type val )
{
	return val.type == 302;
}

bool mtype_isUnsigned_long ( multi_type val )
{
	return val.type == 303;
}

bool mtype_isLong_long ( multi_type val )
{
	return val.type == 304;
}

bool mtype_isUnsignedLong_long ( multi_type val )
{
	return val.type == 305;
}

bool mtype_is_short ( multi_type val )
{
	return val.type == 306;
}

bool mtype_isUnsigned_short ( multi_type val )
{
	return val.type == 307;
}

bool mtype_is_float ( multi_type val )
{
	return val.type == 350;
}

bool mtype_is_double ( multi_type val )
{
	return val.type == 351;
}

bool mtype_is_char ( multi_type val )
{
	return val.type == 100;
}

bool mtype_is_str ( multi_type val )
{
	return val.type == 101;
}

// conversion functions!

int mtype_2_int ( multi_type val )
{
	return * (int *) val.value;
}

unsigned int mtype_2Unsigned_int ( multi_type val )
{
	return * (unsigned int *) val.value;
}

long mtype_2_long ( multi_type val )
{
	return * (long *) val.value;
}

unsigned long mtype_2Unsigned_long ( multi_type val )
{
	return * (unsigned long *) val.value;
}

long long mtype_2Long_long ( multi_type val )
{
	return * (long long *) val.value;
}

unsigned long long mtype_2UnsignedLong_long ( multi_type val )
{
	return * (unsigned long long *) val.value;
}

short mtype_2_short ( multi_type val )
{
	return * ( short *) val.value;
}

unsigned short mtype_2Unsigned_short ( multi_type val )
{
	return * ( unsigned short *) val.value;
}

float mtype_2_float ( multi_type val )
{
	return * (float *) val.value;
}

double mtype_2_double ( multi_type val )
{
	return * (double *) val.value;
}

char mtype_2_char ( multi_type val )
{
	return * (char *) val.value;
}

char * mtype_2_str ( multi_type val )
{
	return (char *) val.value;
}

// ------------------ < / Multi Type Functions > -----------------

// ------------------ < Inherit Functions > ----------------------

void inherit_construct ( actual_obj act_obj, cclass* super, const char* type, ... )
{
	va_list va;
	va_start(va, type);
	if (act_obj == NULL)
	{
		act_obj = malloc(*(super -> size));
		cclass_check_memory(act_obj);
	}
	super -> construct(act_obj, type, va, super->super);
	va_end(va);
}

void inherit_create ( actual_obj act_obj, cclass* super )
{
	if (act_obj == NULL)
	{
		act_obj = malloc(*(super -> size));
		cclass_check_memory(act_obj);
	}
	super -> create(act_obj, super -> super);
}

multi_type inherit_method ( actual_obj act_obj, cclass* super, const char* method_name, ... )
{
	va_list va;
	va_start(va, method_name);
	multi_type m = super -> method(act_obj, method_name, va, super -> super);
	va_end(va);
	return m;
}

void inherit_delete ( actual_obj act_obj, cclass* super )
{
	if ( super -> delete != NULL )
	{
		super -> delete(act_obj, super -> super);
	}
	if ( act_obj != NULL )
	{
		free ( act_obj );
	}
}

// ----------------- < / Inherit Functions > --------------------


// ------------------ < Warn bypass > ----------------------

void warn_bypass( void* thing )
{
	if ( thing == NULL || thing != NULL){}
}

// ------------------ < / Warn bypass > ----------------------