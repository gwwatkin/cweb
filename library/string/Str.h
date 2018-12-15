#ifndef STR_H
#define STR_H

#include <stdlib.h>
#include <string.h>

/**
 * For Ana to continue.
 * <3
 */


typedef struct _Str_t Str_t;





/**
 * Make an uninitialized string of length n
 */
Str_t* Str_new(size_t n);



/**
 * Make a Str_t duplicating a standard null terminated c string
 */
Str_t* Str_dupCStr(char* s);


/**
 * Make a Str_t duplicating a char array of length n
 */
Str_t* Str_dupCStrN(char* s,size_t n);


/**
 * Return a clone of a string
 */
Str_t* Str_clone(Str_t* other);


size_t Str_getLen(Str_t* this);


char* Str_getPointerToCString(Str_t* this);


int Str_compare(Str_t* this, Str_t* other);


void Str_append(Str_t* this, Str_t* other);


void Str_appendCStrN(Str_t* this, char* cstr, int n);


void Str_appendCStr(Str_t* this, char* cstr);


void Str_appendAndFree(Str_t* this, Str_t* other);


char* Str_getNewCStr(Str_t* this);


Str_t* Str_readFromFile(char* filename);


void Str_writeToFile(Str_t* this, char* filename);


void Str_free(Str_t* this);


#endif
