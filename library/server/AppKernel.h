#pragma once

#include "../hashmap/hashmap.h"




/**
 * Manages the environment of the application.
 * 
 * Manages services. Services are objects that provide functionality to our
 * application.
 */
typedef struct _AppKernel_t AppKernel_t;

/*
 * Once a service is registered in the kernel it will be initialized on its
 * first use, then it becomes available for clients of the application with 
 * AppKernel_getService.
 * 
 * A service could be anything.
 */
typedef void Service_t;



/**
 * A serviceHolder is just a wrapper that handles a service internally in
 * the kernel.
 * 
 * It keeps track of the constructor, the constructor arguments and the 
 * deconstructor.
 */
typedef struct _ServiceHolder_t ServiceHolder_t;



AppKernel_t* AppKernel_new();




typedef Service_t* (*ServiceConstructorClosure_t)(void*);
typedef void (*ServiceDeconstructorClosure_t)(Service_t*);

/**
 * A service is not initialized untill it's actually used
 */
void AppKernel_registerService(
    AppKernel_t* this,
    char* name, 
    ServiceConstructorClosure_t constructor,
    void* constructor_parameters,
    ServiceDeconstructorClosure_t deconstructor
);


Service_t* AppKernel_getService(AppKernel_t* this, char* name);




/**
 * When this is called all registered services are also terminated.
 */
void AppKernel_free(AppKernel_t* this);
