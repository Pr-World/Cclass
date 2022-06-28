#ifndef CCLASS_H_INCL
#define CCLASS_H_INCL

#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

/*
the "actual" object is just a void pointer
pointing to the allocated address
*/

typedef void* actual_obj;

/*
multi_type object which contains type to ensure which type is it
and void pointer pointing to that value
*/

typedef struct multi_type
{
	unsigned int type;
	void * value;
}
multi_type;

/*
the "cclass" consists of size [ given in form of address ] to enable runtime support
and inheritence, create function pointer to point to create function of class.
construct to point to construct function and method to point to method function
the super cclass should point to parent class if inherited else it should be NULL
*/

typedef struct cclass
{
	// name of the class
	char* name;

	// size of the class
	size_t* size;

	// object handling functions
	void ( * create ) ( actual_obj , struct cclass* );
	void ( * construct ) ( actual_obj, const char*, va_list, struct cclass* );
	multi_type ( * method ) ( actual_obj, const char*, va_list, struct cclass*);
	void ( * delete ) ( actual_obj, struct cclass* );

	// super or parent or inherited class
	struct cclass* super;
}
cclass;


/*
the external object [ received by the user ] contains the "actual" object
external method and delete functions, internal method and super class + size information
which is static unless object is changed or it is changed explicitly
*/

typedef struct object
{
	actual_obj * self;

	// external use of method and delete
	multi_type ( * method ) ( struct object obj, const char*, ... );
	struct object ( * delete ) ( struct object obj );

	// internal use of method, super class and delete
	multi_type ( * __internal_method ) ( actual_obj, const char*, va_list, cclass * );
	struct cclass* __super;
	void (* __internal_delete ) ( actual_obj, cclass * );

	// size information
	size_t size;
}
object;

// object creation and managing functions
object new ( cclass );
object construct ( cclass, const char*, ... );

/*
------------- Standard "multi_type" Types --------------

< Errors | output codes >

400 : null output but no error
401 : method not found

402 - 499 : reserved for custom error codes of class
[ should be defined by class documentation itself ]

< / Errors | output codes >

< integer family >

300: int
301: unsigned int

302: long
303: unsigned long

304: long long
305: unsigned long long

306: short
307: unsigned short

< / integer family >

< double | float >

350: float
351: double
352: long double

< / double | float >

< character | string >

200: character
201: string

< / character | string >
*/

// ----------------- < multi - type check functions > --------------

bool mtype_is_null ( multi_type );
bool mtype_is_err ( multi_type );

bool mtype_is_int ( multi_type );
bool mtype_isUnsgined_int ( multi_type );

bool mtype_is_long ( multi_type );
bool mtype_isUnsigned_long ( multi_type );

bool mtype_isLong_long ( multi_type );
bool mtype_isUnsignedLong_long ( multi_type );

bool mtype_is_short ( multi_type );
bool mtype_isUnsigned_short ( multi_type );

bool mtype_is_double ( multi_type );
bool mtype_is_float ( multi_type );

bool mtype_is_char ( multi_type );
bool mtype_is_str ( multi_type );

// ------------- < / multi - type check functions > ---------------

// --------------- < multi - type convert functions > ----------------

int mtype_2_int ( multi_type );
unsigned int mtype_2Unsigned_int ( multi_type );

long mtype_2_long ( multi_type );
unsigned long mtype_2Unsigned_long ( multi_type );

long long mtype_2Long_long ( multi_type );
unsigned long long mtype_2UnsignedLong_long ( multi_type );

short mtype_2_short ( multi_type );
unsigned short mtype_2Unsigned_short ( multi_type );

double mtype_2_double ( multi_type );
float mtype_2_float ( multi_type );

char mtype_2_char ( multi_type );
char * mtype_2_str ( multi_type );

// ------------- < / multi - type convert functions > ------------

// ----------- < functions for helping inheritence > --------------

void inherit_construct ( actual_obj, cclass *, const char*, ... );
void inherit_create ( actual_obj, cclass * );
multi_type inherit_method ( actual_obj, cclass *, const char*, ... );
void inherit_delete ( actual_obj, cclass* );

// ----------- < / functions for helping inheritence > --------------

#endif