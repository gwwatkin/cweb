#ifndef VALUE_H
#define VALUE_H

//#include "Array.h"


   /*
    * +------------------------------------------------------------------------
    * | JSON like Value.
    * |------------------------------------------------------------------------
    * | A value can be of any of the value types accepted by a JSON. A complete
    * | list can be found in the ValueType enum.
    * |
    * 
    */ 


typedef enum _valueType 
{
    LONG,
    DOUBLE,
    STRING,
    TRUE,
    FALSE,
    ARRAY,
    OBJECT,
    NOTHING // NULL
} ValueType_t;
 

typedef struct _value
{
    ValueType_t type;
    union
    {
        long num_long;
        double num_double;
        char* string;
    };
    
} Value_t;





Value_t* Value_fromLong(long l);

Value_t* Value_fromDouble(double d);

Value_t* Value_fromString(char* s);

Value_t* Value_copy(Value_t* v);


void Value_destroy(Value_t* v);




#endif
