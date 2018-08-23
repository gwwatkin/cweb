#include "Route.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../utils.h"


struct _Route_t
{
    // Path is relative, that is if this route is a subroute of some other 
    // route the matching will continue past what's allready been matched.
    char* path;
    
    Method_t method;
    
    // Used to refernce
    char* name;
    
    // Executed if not NULL;
    HandlerClosure_t handler; 
    
    // If handler returns HANDLER_CONTINUE continue matching the children.
    vector_t* subroutes; 
    
    // If handler returns HANDLER_ABORT, or no matching subroute is found call.
    // If null, call the parents handler passing the return status
    FallbackHandlerClosure_t fallback_handler; 
};




Route_t* Route_new(char* path, Method_t method, char* name, HandlerClosure_t handler)
{
    Route_t* this = malloc(sizeof(Route_t));
    
    this->path = strdup(path);
    this->method = method;
    this->name = strdup(name);
    this->handler = handler;
    
    this->subroutes = vector_new();
    
    return this;
}




void Route_addSubroute(Route_t* this, Route_t* other_route)
{
    vector_push(this->subroutes,other_route);
}



void Route_setFallback(Route_t* this, FallbackHandlerClosure_t fallback_handler)
{
    this->fallback_handler = fallback_handler;
}



HandlerReturnStatus_t Route_runFallBack_(Route_t* this, AppKernel_t* app, HandlerReturnStatus_t status)
{
    if(this->fallback_handler != NULL)
        return (this->fallback_handler)(app,status);
        
    return status;
}



HandlerReturnStatus_t Route_handle(Route_t* this, AppKernel_t* app, char* uri)
{
    if( strlen(uri)<strlen(this->path)
        || strncmp(this->path, uri, strlen(this->path))!=0
      )
        return HANDLER_NO_MATCH;
    
    HandlerReturnStatus_t current_node_return_status = Route_handleThis_(this,app);

    if(strlen(uri)>0 && current_node_return_status==HANDLER_CONTINUE)
    {
        // The uri is not entirely consumed and we can continue.
        // Find the first matching subroute, consume the uri string and continue.
        Route_passToSubroutes_(this,app,uri);
    }
    
    return current_node_return_status;
}




HandlerReturnStatus_t Route_passToSubroutes_(Route_t* this,AppKernel_t* app,char* uri)
{
    HandlerReturnStatus_t ret;
    
    int len = vector_lenght(this->subroutes);
    for(int i= 0; i<len; i++)
    {
        Route_t* subroute = vector_at(this->subroutes,i);

        //consume the uri string
        ret =  Route_handle(subroute, app, uri);
        
        //on a handle we stop
        if(ret == HANDLER_HANDLED)
            return HANDLER_HANDLED;
        
        //this is an error
        if(ret != HANDLER_NO_MATCH)
            return Route_runFallBack_(this,app,ret);
    } 
        
    return Route_runFallBack_(this,app,HANDLER_NOT_FOUND);
}

HandlerReturnStatus_t Route_handleThis_(Route_t* this, AppKernel_t* app)
{
    if(this->handler==NULL)
        return HANDLER_CONTINUE;
    
    return (*this->handler)(app);
}




void Route_dump(Route_t* this,int indent)
{
    pindent(indent);
    printf("Route at <%lx>:\n",(unsigned long) this);
    pindent(indent);
    printf("{\n");
    indent++;
    pindent(indent);
    printf("path:%s\n",this->path);
    pindent(indent);
    printf("method:%i\n",this->method);
    pindent(indent);
    printf("name:%s\n",this->name);
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
    free(this->path);
    this->path = NULL;
    
    free(this->name);
    this->name = NULL;
    
    for(int i = 0; i<vector_lenght(this->subroutes); i++)
        Route_free(vector_at(this->subroutes,i));
    
    vector_free(this->subroutes);
    this->subroutes = NULL;
    
    free(this);
}
