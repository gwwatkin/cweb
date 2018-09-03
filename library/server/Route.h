#pragma once

#include "Request.h"
#include "Response.h"
#include "AppKernel.h"
#include "../Path.h"

#include "../vector/vector.h"
 




typedef enum _HandlerReturnStatus_t
{
    
    HANDLER_HANDLED = 0,
    
    HANDLER_CONTINUE = 1,
    
    HANDLER_ABORT = 2,
    
    HANDLER_NOT_FOUND = 3,
    
} HandlerReturnStatus_t;



typedef HandlerReturnStatus_t (*HandlerClosure_t)(AppKernel_t*);

typedef HandlerReturnStatus_t (*FallbackHandlerClosure_t)(AppKernel_t*,HandlerReturnStatus_t);


/**
 * Routes are organized in a tree like structure.
 * The path of a subroute is relative to the parent.
 *
 * (more docs)
 */
typedef struct _Route_t Route_t;



Route_t* Route_new(
    char* path_token, 
    Method_t method,
    char* name,
    HandlerClosure_t handler,
    FallbackHandlerClosure_t fallback_handler
);


/** 
 * Call all the handlers that are in the path specified by the uri as long as
 * they return HANDLER_CONTINUE.
 * 
 * If another staus is returned, or no matching handler is found, the fallback 
 * handler is called with the status returned by the unsucessful handler or 
 * HANDLER_NOT_FOUND respectively.
 */
HandlerReturnStatus_t Route_handle(Route_t* this, AppKernel_t* kernel, Path_t* path);



/** 
 * Define a subroute.
 * Passes memory management to parent.
 */
void Route_addSubroute(Route_t* this, Route_t* other_route);




/** Display debug information */
void Route_dump(Route_t* this,int indent);



void Route_free(Route_t* this);


