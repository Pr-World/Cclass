#include "cclass.h"

// ---------------- < Object Functions > --------------------
object obj_create( cclass class )
{
	object o;
	
	o.self = malloc(class.size);
	o.parent = &class;
	
	// calling the create function!
	o.parent -> create(o.self);

	return o;
}

object obj_construct ( cclass class, const char* type, ... )
{
	va_list va;
	va_start(va, type);
	object o;

	o.self = malloc(class.size);
	o.parent = &class;

	// calling the construct function!
	o.parent -> construct(o.self, type, va);

	va_end(va);

	return o;
}

object obj_delete ( object obj )
{
	// free the memory
	free(obj.self);
	
	// point it's parent to null
	obj.parent = NULL;

	// return the object
	return obj;
}

multi_type obj_method ( object obj, const char* method_name, ... )
{
	va_list va;
	va_start(va, method_name);

	multi_type return_val = obj.parent -> method(obj.self, method_name, va);

	va_end(va);
	
	return return_val;
}
// ------------------ < / Object Functions > ------------------

// ------------------- < Multi Type Functions > -----------------
bool mtype_is_null ( multi_type val ){
	return val.type == 0;
}

// ------------------ < / Multi Type Functions > -----------------