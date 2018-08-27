#include "AppKernel.h"

#include <stdlib.h>
#include <string.h>

//debug
#include <stdio.h>


#include "../hashmap/hashmap.h"

struct _ServiceHolder_t{
    
    Service_t* service_object;
    
        
    ServiceConstructorClosure_t constructor;
    void* constructor_parameters;
    
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



void AppKernel_setService(
    AppKernel_t* this,
    char* name,
    Service_t* service,
    ServiceDeconstructorClosure_t deconstructor)
{
    ServiceHolder_t* holder = malloc(sizeof(ServiceHolder_t));
    holder->service_object = service;
    holder->deconstructor = deconstructor;
    
    hashmap_put(this->service_holders,name,holder);
}



void AppKernel_registerService(
    AppKernel_t* this,
    char* name,
    ServiceConstructorClosure_t constructor,
    void* constructor_parameters,
    ServiceDeconstructorClosure_t deconstructor
)
{
    ServiceHolder_t* holder = malloc(sizeof(ServiceHolder_t));
    
    holder->constructor_parameters = constructor_parameters;
    holder->deconstructor = deconstructor;
    
    hashmap_put(this->service_holders,name,holder);
    
}





Service_t* AppKernel_getService(AppKernel_t* this, char* name)
{
    ServiceHolder_t* holder = hashmap_at(this->service_holders,name);
    if(holder== NULL)
        return NULL;
    
    if(!holder->service_object)
        holder->service_object  =
            (*holder->constructor)(holder->constructor_parameters);
        
    return holder->service_object;
}



void AppKernel_freeService(AppKernel_t* this,char* name)
{
    ServiceHolder_t* holder = hashmap_at(this->service_holders,name);
    
    if(holder==NULL)
        return;
    
    if(holder->deconstructor)
        (holder->deconstructor)(holder->service_object,holder->constructor_parameters);
    
    free(holder);
    
    hashmap_remove(this->service_holders,name);
}


void AppKernel_free(AppKernel_t* this)
{
    int i;
    char* service_name;
    
    
    //free all services by calling their deconstructor.
    vector_t* keys = hashmap_keysRef(this->service_holders);
    foreach(keys,i,service_name)
        AppKernel_freeService(this,service_name);
    
    vector_free(keys);
    
    hashmap_free(this->service_holders);
    
    free(this);
}
