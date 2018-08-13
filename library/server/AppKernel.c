#include "AppKernel.h"


#include "../hashmap/hashmap.h"

#include <stdlib.h>




struct _ServiceHolder_t{

    char service_initialized;
    
    union{
        Service_t* service_object;
        
        struct{
            void* constructor_parameters;
            ServiceConstructorClosure_t constructor;
        };
    };
    
    ServiceDeconstructorClosure_t deconstructor;
};



struct _AppKernel_t
{
    hashmap_t* service_holders;
};


AppKernel_t* AppKernel_new()
{
    AppKernel_t* this = malloc(sizeof(AppKernel_t));
    
    this->service_holders = hashmap_new();
    
    return this;
}



//continue here by implementing the missing methods

void AppKernel_registerService(AppKernel_t* this, char* name, ServiceConstructorClosure_t constructor, void* constructor_parameters, ServiceDeconstructorClosure_t deconstructor)
{
}

Service_t * AppKernel_getService(AppKernel_t* this, char* name)
{
}




void AppKernel_free(AppKernel_t* this)
{
    //free all services by calling their own deconstructor on them.
    
    free(this);
}
