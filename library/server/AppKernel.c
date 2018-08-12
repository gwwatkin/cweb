#include "AppKernel.h"

#include <stdlib.h>


AppKernel_t* AppKernel_new()
{
    return malloc(sizeof(AppKernel_t));
}


void AppKernel_registerRoutes(AppKernel_t* this,Route_t* root)
{

}


void AppKernel_free(AppKernel_t* this)
{
    
    
    free(this);
}
