#include "Value.h"

#include <string.h>


Value_t* Value_fromLong(long l)
{    
    Value_t * out = malloc(sizeof(Value_t));
    
    out->type = LONG;
    out->num_long = l;
    
    return out;
}

Value_t* Value_fromDouble(double d)
{    
    Value_t * out = malloc(sizeof(Value_t));
    
    out->type = DOUBLE;
    out->num_double = d;
    
    return out;
}

Value_t* Value_fromString(char* s)
{    
    Value_t * out = malloc(sizeof(Value_t));
    
    out->type = STRING;
    out->string = strdup(s);
    
    return out;
}

Value_t* Value_copy(Value_t* v)
{   
    switch(v->type)
    {
        case LONG:
            return Value_fromLong(v->num_long);
        
        case DOUBLE:
            return Value_fromDouble(v->num_double);
      
        case STRING:
            return Value_fromString(v->string);
            
        default:
            return NULL;
    }
    
}




void Value_destroy(Value_t* v)
{   
    switch(v->type)
    {
        case STRING:
            free(v->string);
        default:
            return;
    }
    
}
