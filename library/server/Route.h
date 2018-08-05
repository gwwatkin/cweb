#pragma once

#include "Request.h"
#include "Response.h"
#include "../vector/vector.h"


typedef enum _HandlerReturnStatus_t
{
    HANDLER_CONTINUE = 0,
    HANDLER_TERMINATE = 1,
    
}HandlerReturnStatus_t;



typedef HandlerReturnStatus_t (*handler)(Request_t*,Response_t*)
    HandlerClosure_t;



typedef struct _Route
{
    // Path is relative, that is if this route is a subroute of some other 
    // route the matching will continue past what's allready been matched.
    char* path;
    
    Method_t method;
    
    //used to refernce
    char* name;
    
    //executed if not NULL;
    HandlerClosure_t handler; 
    
    //if handler returns HANDLER_CONTINUE continue matching
    vector_t* subroutes; 
        
    }
}Route_t;



Route_t* Route_new(char* path, Method_t method, char* name); 


void* Route_addSubroute(Route_t* this, Route_t* other_route);


void Route_free(Route_t* this);




