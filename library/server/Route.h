#pragma once

#include "Request.h"
#include "Response.h"
#include "AppKernel.h"

#include "../vector/vector.h"
 




typedef enum _HandlerReturnStatus_t
{
    
    HANDLER_HANDLED = 0,
    
    HANDLER_CONTINUE = 1,
    
    HANDLER_ABORT = 2,
    
    HANDLER_NOT_FOUND = 3,
    
    HANDLER_NO_MATCH = 4,
    
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



Route_t* Route_new(char* path, Method_t method, char* name, HandlerClosure_t handler); 


/** 
 * Call all the handlers that are in the path specified by the uri as long as
 * they return HANDLER_CONTINUE.
 * 
 * If another staus is returned, or no matching handler is found, the fallback handler
 * is called with, the status returned by the unsucessful handler or HANDLER_NOT_FOUND
 * respectively.
 */
HandlerReturnStatus_t Route_handle(Route_t* this, AppKernel_t* app, char* uri);



/** 
 * Define a subroute.
 * Passes memory management to parent
 */
void Route_addSubroute(Route_t* this, Route_t* other_route);





/** 
 * Fallback route is called when the URI is not found.
 * If not set then the parent's fallback handler is called.
 */ 
void Route_setFallback(Route_t* this,FallbackHandlerClosure_t fallback_handler);





/** private methods */




/** 
 * Call this route's handler, if no handler was specified return handler continue.
 */
HandlerReturnStatus_t Route_handleThis_(Route_t* this, AppKernel_t* app);


/**
 * Same as Route_handle, but ignore the current node.
 */
HandlerReturnStatus_t Route_passToSubroutes_(Route_t* this,AppKernel_t* app,char* uri);


/** 
 * Called when a handler returns a status different from HANDLER_CONTINUE or HANDLER_HANDLED
 */
HandlerReturnStatus_t Route_runFallBack_(Route_t* this,AppKernel_t* app ,HandlerReturnStatus_t status);


/** Display debug information */
void Route_dump(Route_t* this,int indent);



void Route_free(Route_t* this);




