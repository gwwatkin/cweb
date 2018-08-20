#pragma once

#include "Request.h"
#include "Response.h"
#include "AppKernel.h"

#include "../vector/vector.h"
 




typedef enum _HandlerReturnStatus_t
{
    HANDLER_CONTINUE = 0,
    HANDLER_TERMINATE = 1,
    HANDLER_HANDLED = 3,
    HANDLER_NOT_FOUND = 4,
    
} HandlerReturnStatus_t;



typedef HandlerReturnStatus_t (*HandlerClosure_t)(AppKernel_t*);




/**
 * Routes are organized in a tree like structure.
 * The path of a subroute is relative to the parent.
 *
 * (more docs)
 */
typedef struct _Route_t Route_t;



Route_t* Route_new(char* path, Method_t method, char* name, HandlerClosure_t handler); 

/** 
 * Fallback route is called when the URI is not found.
 * If not set then the parent's fallback handler is called.
 */ 
void Route_setFallback(Route_t* this,HandlerClosure_t fallback_handler);


/** 
 * Define a subroute.
 * Passes memory management to parent
 */
void Route_addSubroute(Route_t* this, Route_t* other_route);


/** 
 * Call all the handler that are in the path specified by the URI.
 * 
 * If the return status is HANDLER_NOT_FOUND, no handler ha
 * 
 * When fallback is called it returns HANDLER_HANDLED.
 */
HandlerReturnStatus_t Route_handle(Route_t* this, AppKernel_t* app, char* uri);



/** Call this route's handler */
HandlerReturnStatus_t Route_handleThis(Route_t* this, AppKernel_t* app);


/** Display debug information */
void Route_dump(Route_t* this,int indent);



void Route_free(Route_t* this);




