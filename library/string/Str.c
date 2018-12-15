#include "Str.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

#define BUFFER_SIZE 1024


struct _Str_t{
    char* ptr;  
    size_t len;
};





Str_t* Str_new(size_t n)
{
    Str_t* this = malloc(sizeof(Str_t));
    this->ptr = malloc(sizeof(char));
    this->len = 0;
    return this;
}




Str_t* Str_dupCStr(char* s)
{
    int len = strlen(s);
    // trim the null charachter
    if(s[len-1] == '\0')
        len--;
    
    return Str_dupCStrN(s,len);
}


/**
 * Make a Str_t duplicating a char array of length n
 */
Str_t* Str_dupCStrN(char* s,size_t n)
{
    Str_t* this = malloc(sizeof(Str_t));
    this->len = n;
    this->ptr = strndup(s,n);
    
    return this;
}



Str_t* Str_clone(Str_t* other)
{
    return Str_dupCStrN(other->ptr,other->len);
}


size_t Str_getLen(Str_t* this)
{
    return this->len;
}


char* Str_getPointerToCString(Str_t* this)
{
    return this->ptr;
}

int Str_compare(Str_t* this, Str_t* other)
{
    int comparison = strncmp(this->ptr, other->ptr, MIN(this->len,other->len));
    if(comparison!= 0)
        return comparison;
    else 
        return this->len - other->len;
    
}




void Str_appendCStrN(Str_t* this, char* cstr, int n)
{
    if(n==0)
        return;
    
    this->ptr = realloc(this->ptr, this->len+n);
    strncpy(this->ptr+this->len, cstr, n);
    this->len += n;
}


void Str_appendCStr(Str_t* this, char* cstr)
{
    int cstrlen = strlen(cstr);
    if(cstr[cstrlen-1]=='\0')
        cstrlen--;
    
    Str_appendCStrN(this,cstr,cstrlen);
}


void Str_append(Str_t* this, Str_t* other)
{
    Str_appendCStrN(this,other->ptr,other->len);
}


void Str_appendAndFree(Str_t* this, Str_t* other)
{
    Str_append(this,other);
    Str_free(other);
}



char* Str_getNewCStr(Str_t* this)
{
    return strndup(this->ptr,this->len);
}




Str_t * Str_readFromFile(char* filename)
{
    FILE* f = fopen(filename, "r");
    
    if(f == NULL)
    {
        printf("Error: Unable to open file\n");
        return NULL;
    }
    
    
    Str_t* output = Str_new(0);
    
    char buffer[BUFFER_SIZE];
    
    while(fgets(buffer, BUFFER_SIZE, f) != NULL) 
    {
        //buffer[BUFFER_SIZE-1] = '\0';
        Str_appendCStr(output,buffer);
    } 
    
    fclose(f);
    
    return output;
}


void Str_writeToFile(Str_t* this, char* filename)
{

    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        printf("Error: Unable to open file\n");
    }

    fwrite(this->ptr, sizeof(char), this->len, f);

    fclose(f);
    
}




void Str_free(Str_t* this)
{
    free(this->ptr);
    free(this);
}


