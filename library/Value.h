#ifndef VALUE_H
#define VALUE_H

#include "Array.h"

typedef enum _valueType 
{
    LONG,
    DOUBLE,
    STRING,
    ARRAY,
    OBJECT,
    NULL
} ValueType_t;
 
 
 
 
 
//Available types of a value

typedef struct _value
{
    ValueType_t type;
    
    union
    {
        long num_long;
        double num_double;
        char* string;
    }
        
    
}

#endif
