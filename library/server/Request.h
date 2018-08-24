#pragma once

#include "../../vendor/onion/src/onion/types.h"

typedef enum _Method_t
{
    //These correspond directly to onion method numbers in 'request.h'
    GET = 0,
    POST = 1,
    HEAD = 2,
    OPTIONS = 3,
    PROPFIND = 4,
    PUT = 5,
    DELETE = 6,
    MOVE = 7,
    MKCOL = 8,
    PROPPATCH = 9,
    PATCH = 10
    
} Method_t;



typedef struct _Request_t Request_t;



Request_t* Request_fromOnion(onion_request* request,int o_reques_free_flag);

const char* Request_getPath(Request_t *);

void Request_free(Request_t* this);
