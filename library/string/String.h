#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <string.h>
#include <../vector>

/**
 * For Ana to continue.
 * <3
 */

typedef struct{
    char* ptr;  
    size_t len;
} Str_t;





/**
 * Make a Str_t from a standard null terminated c string
 */
Str_t Str(char* s)
{
    Str_t str;
    str.len = strlen(s);
    str.ptr = s;
    
    return str;
}



/**
 * Make a Str_t duplicating a standard null terminated c string
 */
Str_t Str_dupCStr(char* s)
{
    Str_t str;
    str.len = strlen(s);
    str.ptr = strdup(s);
    
    return str;
}


/**
 * Make a Str_t duplicating a char array of length n
 */
Str_t Str_dupCStrN(char* s,size_t n)
{
    Str_t str;
    str.len = n;
    str.ptr = strndup(s,n);
    
    return str;
}



Str_t Str_copy(Str_t str)
{
    Str_t str1;
    str1.len = str.len;
    str1.ptr = strndup(str.ptr,str.len);
    
    
    return str1; 
}



void Str_free(Str_t str)
{
    free(str.ptr);
    str.ptr = NULL;
}

#endif
