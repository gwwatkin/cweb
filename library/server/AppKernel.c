#include "AppKernel.h"


#include "../hashmap/hashmap.h"

#include <stdlib.h>
#include <string.h>



struct _ServiceHolder_t{

    char is_initialized;
    
    union{
        Service_t* service_object;
        
        struct{
            ServiceConstructorClosure_t constructor;
            void* constructor_parameters;
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

void AppKernel_registerService(
    AppKernel_t* this,
    char* name,
    ServiceConstructorClosure_t constructor,
    void* constructor_parameters,
    ServiceDeconstructorClosure_t deconstructor
)
{
    ServiceHolder_t* holder = malloc(sizeof(ServiceHolder_t));
    
    holder->is_initialized = 0;
    holder->constructor_parameters = constructor_parameters;
    holder->deconstructor = deconstructor;
    
    hashmap_put(this->service_holders,strdup(name),holder);
    
}





Service_t * AppKernel_getService(AppKernel_t* this, char* name)
{
    ServiceHolder_t* holder = hashmap_at(this->service_holders,name);
    if(holder== NULL)
        return NULL;
    
    if(!holder->is_initialized)
    {
        Service_t* service_object  =
            (*holder->constructor)(holder->constructor_parameters);
    
        if(service_object == NULL)
            return NULL;
        
        holder->service_object = service_object;
    }
   
        
    return holder->service_object;
}




void AppKernel_free(AppKernel_t* this)
{
    //free all services by calling their own deconstructor on them.
    
    free(this);
}
