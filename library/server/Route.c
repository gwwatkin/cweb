#include "Route.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../utils.h"


struct _Route_t
{
    // Path is relative, that is if this route is a subroute of some other 
    // route the matching will continue past what's allready been matched.
    char* path_token;
    
    Method_t method;//unused at the moment
    
    // Executed if not NULL;
    HandlerClosure_t handler; 
    
    // If handler returns HANDLER_CONTINUE continue matching the children.
    vector_t* subroutes; 
    
    // If handler returns HANDLER_ABORT, or no matching subroute is found call.
    // If null, call the parents handler passing the return status
    FallbackHandlerClosure_t fallback_handler; 
};









// BEGIN private methods



/** 
 * Call this route's handler, if no handler was specified return handler 
 * continue.
 */
HandlerReturnStatus_t Route_callCurrentHandler_(Route_t* this, AppKernel_t* kernel);


/**
 * Same as Route_handle, but ignore the current node.
 */
HandlerReturnStatus_t Route_passToSubroutes_(
    Route_t* this,
    AppKernel_t* kernel,
    Path_t* path
);


/** 
 * Called when a handler returns a status different from HANDLER_CONTINUE or HANDLER_HANDLED.
 */
HandlerReturnStatus_t Route_runFallBackHandler_(
    Route_t* this,
    AppKernel_t* kernel,
    HandlerReturnStatus_t status
);

// END private methods 









Route_t* Route_new(
    const char* path_token, 
    Method_t method,
    HandlerClosure_t handler,
    FallbackHandlerClosure_t fallback_handler
)
{
    Route_t* this = malloc(sizeof(Route_t));
    
    this->path_token = strdup(path_token);
    this->method = method;
    this->handler = handler;
    this->fallback_handler = fallback_handler;
    
    this->subroutes = vector_new();
    
    return this;
}




void Route_addSubroute(Route_t* this, Route_t* other_route)
{
    vector_push(this->subroutes,other_route);
}






HandlerReturnStatus_t Route_handle(
    Route_t* this,
    AppKernel_t* kernel,
    Path_t* path)
{
    
    HandlerReturnStatus_t status = Route_callCurrentHandler_(this,kernel);

    if(status==HANDLER_CONTINUE)
        status = Route_passToSubroutes_(this,kernel,path);
    
    if(status!=HANDLER_HANDLED)
        status = Route_runFallBackHandler_(this,kernel,status);
        
    return status;
}




HandlerReturnStatus_t Route_passToSubroutes_(
    Route_t* this,
    AppKernel_t* kernel,
    Path_t* path)
{
    int i;
    Route_t* subroute;

    
    if(!vector_lenght(this->subroutes))
        return HANDLER_HANDLED;

    foreach(this->subroutes,i,subroute)
    {
        if(Path_tryToConsume(path,subroute->path_token))
            return Route_handle(subroute,kernel,path);
    }
        
    return HANDLER_NOT_FOUND;
}




HandlerReturnStatus_t Route_runFallBackHandler_(
    Route_t* this,
    AppKernel_t* kernel,
    HandlerReturnStatus_t status)
{
    if(this->fallback_handler != NULL)
        return (this->fallback_handler)(kernel,status);
        
    return status;
}




HandlerReturnStatus_t Route_callCurrentHandler_(Route_t* this, AppKernel_t* kernel)
{
    if(this->handler==NULL)
        return HANDLER_CONTINUE;
    
    return (*this->handler)(kernel);
}




void Route_dump(Route_t* this,int indent)
{
    pindent(indent);
    printf("Route at <%lx>:\n",(unsigned long) this);
    pindent(indent);
    printf("{\n");
    indent++;
    pindent(indent);
    printf("path:%s\n",this->path_token);
    pindent(indent);
    printf("method:%i\n",this->method);
    pindent(indent);
    printf("handler:%lx\n",(unsigned long) this->handler);
    pindent(indent);
    printf("subroutes:\n");
    pindent(indent);
    printf("{\n");
    indent++;
    for(int i = 0; i< vector_lenght(this->subroutes); i++)
        Route_dump(vector_at(this->subroutes,i),indent);
    indent--;
    pindent(indent);
    printf("}\n");
    
    
    indent--;
    
    pindent(indent);
    printf("}\n");
}




void Route_free(Route_t* this)
{
    free(this->path_token);
    this->path_token = NULL;
    
    
    for(int i = 0; i<vector_lenght(this->subroutes); i++)
        Route_free(vector_at(this->subroutes,i));
    
    vector_free(this->subroutes);
    this->subroutes = NULL;
    
    free(this);
}
