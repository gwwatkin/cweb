#pragma once

#include "Request.h"
#include "Response.h"
#include "AppKernel.h"
#include "../vector/vector.h"



typedef enum _HandlerReturnStatus_t
{
    HANDLER_CONTINUE = 0,
    HANDLER_TERMINATE = 1,
    
} HandlerReturnStatus_t;



typedef HandlerReturnStatus_t (*HandlerClosure_t)(AppKernel_t*,Request_t*,Response_t*);



typedef struct _Route
{
    // Path is relative, that is if this route is a subroute of some other 
    // route the matching will continue past what's allready been matched.
    char* path;
    
    Method_t method;
    
    // Used to refernce
    char* name;
    
    // Executed if not NULL;
    HandlerClosure_t handler; 
    
    // If handler returns HANDLER_CONTINUE continue matching the children.
    vector_t* subroutes; 
        

}Route_t;



Route_t* Route_new(char* path, Method_t method, char* name, HandlerClosure_t handler); 


/** Passes memory management to parent */
void Route_addSubroute(Route_t* this, Route_t* other_route);


/** Display debug information */
void Route_dump(Route_t* this);

void Route_free(Route_t* this);




