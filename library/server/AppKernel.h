#pragma once

#include "Request.h"
#include "Response.h"
#include "Route.h"

typedef struct _AppKernel_t
{
    Route_t * root;
    
}AppKernel_t;


AppKernel_t* AppKernel_new();


void AppKernel_registerRoutes(AppKernel_t* this,Route_t* root);


void AppKernel_free(AppKernel_t* this);
