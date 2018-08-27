#include "Request.h"

#include <stdlib.h>

#include "../../vendor/onion/src/onion/request.h"

struct _Request_t {
    
    onion_request* o_request;
    int o_request_free;
};



Request_t* Request_fromOnion(onion_request* request,int o_request_free_flag)
{
    Request_t* this = malloc(sizeof(Request_t));
    this->o_request = request;
    this->o_request_free = o_request_free_flag;
    
    return this;
}



const char * Request_getPath(Request_t* this)
{
    return onion_request_get_path(this->o_request);
}



void Request_free(Request_t* this)
{
    //maybe there should be a macro for this...
    if(this == NULL)
        return;
    
    free(this);
}
