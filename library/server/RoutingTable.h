#pragma once

#include "Request.h"
#include "ResponseGenerator.h"

typedef enum  
{   
    UNDEFINED=-1,
    GET,
    HEAD,
    POST,
    PUT,
    PATCH,
    DELETE,
    OPTIONS,
} Method;


typedef struct _route
{
    char* url;
    Method method;
    ResponseGenerator_t (* controller)(Request_t *);
    
} Route_t;


typedef struct _routingTable
{
    int number_of_routes;
    Route_t * routes;
        
} RoutingTable_t;


