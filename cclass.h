#ifndef CCLASS_H_INCL
#define CCLASS_H_INCL

#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void* actual_obj;

typedef struct multi_type
{
	unsigned type;
	void * value;
}
multi_type;

typedef struct cclass
{
	size_t size;
	void ( * create ) ( actual_obj );
	void ( * construct ) ( actual_obj, const char*, va_list );
	multi_type ( * method ) ( actual_obj, const char*, va_list );
}
cclass;

typedef struct object
{
	cclass * parent;
	actual_obj * self;
}
object;


// object creation and managing functions
object obj_create ( cclass );
object obj_construct ( cclass, const char*, ... );
object obj_delete ( object );
multi_type obj_method ( object, const char*, ... );

// multi_type check functions
bool mtype_is_null ( multi_type );
bool mtype_is_int ( multi_type );
bool mtype_isUnsgined_int ( multi_type );
bool mtype_is_char ( multi_type );
bool mtype_is_str ( multi_type );
bool mtype_is_long ( multi_type );
bool mtype_isUnsigned_long ( multi_type );
bool mtype_isLong_long ( multi_type );
bool mtype_isUnsignedLong_long ( multi_type );
bool mtype_is_double ( multi_type );
bool mtype_is_float ( multi_type );

// multi_type convert functions
int mtype_2_int ( multi_type );
unsigned int mtype_2Unsigned_int ( multi_type );
char mtype_2_char ( multi_type );
char* mtype_2_str ( multi_type );
long mtype_2_long ( multi_type );
unsigned long mtype_2Unsigned_long ( multi_type );
int mtype_2Long_long ( multi_type );
int mtype_2UnsignedLong_long ( multi_type );
int mtype_2_double ( multi_type );
int mtype_2_float ( multi_type );

#endif