#include "Response.h"

#include <onion/response.h>

#include <stdlib.h>
#include <string.h>

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

void Response_free(Response_t* this)
{
    free(this->body);
    free(this);
}


void Response_setBody(Response_t* this, char* body, int body_size)
{
    
    if(this->body_size>0)
        this->body = realloc(this->body,body_size);
    else
        this->body = malloc(body_size);
    
    
    memcpy(this->body,body,body_size);
    this->body_size = body_size;
}





void Response_writeToOnion(Response_t* this, onion_response* o_response)
{
    
    onion_response_set_code(o_response,200);
    onion_response_write_headers(o_response);
    
    onion_response_write(o_response,this->body,this->body_size);
    
    onion_response_flush(o_response);
}
