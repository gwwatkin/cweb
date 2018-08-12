#pragma once

#include "Request.h"
#include "Response.h"
#include "Route.h"



/**
 * Manages the environment of the application.
 * 
 * Manages subsystems (database, session, cache ...), can handle requests and
 * console commands
 */

typedef struct _AppKernel_t
{
    Route_t* root;
    
}AppKernel_t;


AppKernel_t* AppKernel_new();

/**
 * Register the routes for the kernel.
 */
void AppKernel_registerRoutes(AppKernel_t* this, Route_t* root);

/** @return html response code */
int AppKernel_handleRequest(Request_t* request);

void AppKernel_free(AppKernel_t* this);
