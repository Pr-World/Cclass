#include "person.h"
#include <stdio.h>
#include <string.h>

typedef struct
{
	char name[20];
	int age;
	char gender;
}Person_Struct;

// Creation of object heres
void  Person_Create ( actual_obj act_obj, cclass* super )
{
	// unused parameters warn bypass
	warn_bypass(super);

	// makeup 'this' object / variable
	Person_Struct* this = ( Person_Struct* ) act_obj;

	strcpy(this -> name, "[ NO NAME ]");
	this -> age = 0;
	this -> gender = 'N'; // No gender at start

}

// Construct here
void Person_Construct ( actual_obj act_obj, const char* type, va_list args, cclass* super )
{
	// unused parameters warn bypass
	warn_bypass(super);

	// makeup 'this' object / variable
	Person_Struct* this = ( Person_Struct* ) act_obj;
	
	if ( strcmp(type, "NameAgeGender") == 0 )
	{
		strcpy(this -> name, va_arg(args, char *));
		this -> age = va_arg(args, int);
		this -> gender = va_arg(args, int);
	}
	else
	{
		Person_Create(act_obj, super);
	}
}

// Method of object
multi_type Person_Method( actual_obj act_obj, const char* method_name, va_list args, cclass* super )
{
	// unused parameters warn bypass
	warn_bypass(super);
	warn_bypass(&args);

	// makeup 'this' object / variable
	Person_Struct* this = ( Person_Struct* ) act_obj;
	
	// make the default return value null with no error
	multi_type toReturn = {400, NULL};

	if ( strcmp(method_name, "print") == 0 )
	{
		printf(
			"---- Person: %s ----\nName: %s\nAge: %d\nGender: %c\n",
			this -> name, this -> name, this -> age, this -> gender
		);
		return toReturn;
	}
	else if ( strcmp(method_name, "getName") == 0 )
	{
		toReturn.value = this -> name;
		// string
		toReturn.type = 201;
		return toReturn;
	}
	else if ( strcmp(method_name, "getAge") == 0 )
	{
		toReturn.value = &(this -> age);
		// integer
		toReturn.type = 300;
		return toReturn;
	}else if ( strcmp(method_name, "getGender") == 0 )
	{
		toReturn.value = &(this -> gender);
		// character
		toReturn.type = 200;
		return toReturn;
	}
	else
	{
		// function not found error
		toReturn.type = 401;
		return toReturn;
	}
}

// code when the object is about to be deleted [ if you need to free memory n stuff ]
void Person_Delete( actual_obj obj, cclass* super )
{
	// unused parameters warn bypass
	warn_bypass(obj);
	warn_bypass(super);
}

// sizeof class
size_t Person_Size = sizeof(Person_Struct);

cclass person = {
	"Person",
	&Person_Size,
	Person_Create,
	Person_Construct,
	Person_Method,
	Person_Delete,
	NULL // because we don't have inheritence
};