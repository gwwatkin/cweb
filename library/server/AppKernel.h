#pragma once

#include <stdio.h>
#include <request.h>



/**
 * The AppKernel interfaces the internal components of the framework with the
 * users application by registering the components that the user can use to
 * build the application.
 * 
 * The server creates an AppKernel for every request.
 */


typedef struct _AppKernel
{
    FILE* inputStream;
    FILE* inputStream;
    
} AppKernel_t;



/**
 * Initialize an application, with all the relevant subsystems (i.e. router,session, 
 * database,HttpEngine...)
 */
AppKernel_t* AppKernel_new();


int AppKernel_registerRoutes(RoutingTable* t);

/**
 * Process the request and formulate a response.
 */
int AppKernel_respond();

/**
 * NOTE this doesn't close the file streams.
 */
void AppKernel_finalize(AppKernel_t* k);
