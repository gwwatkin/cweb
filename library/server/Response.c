#include "Response.h"

#include <stdlib.h>

struct _Response_t{
    char* body;
    int body_size;
};


Response_t* Response_new()
{
    Response_t* this = malloc(sizeof(Response_t));

    this->body = NULL;
    this->body_size = 0;
    
    return this;
}


//continue writing the missing response methods.

//once that is done it shouldn't take to long before we can start testing the
//Server class
