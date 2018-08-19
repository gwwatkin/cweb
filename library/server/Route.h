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



typedef HandlerReturnStatus_t (*HandlerClosure_t)(AppKernel_t*);




/**
 * Routes are organized in a tree like structure:
 * 
 * 
 */
typedef struct _Route_t Route_t;


/**
 * path is relative to the parent of the root
 */
Route_t* Route_new(char* path, Method_t method, char* name, HandlerClosure_t handler); 


/** Passes memory management to parent */
void Route_addSubroute(Route_t* this, Route_t* other_route);


/** Display debug information */
void Route_dump(Route_t* this,int indent);

void Route_free(Route_t* this);




