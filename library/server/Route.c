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
    
    //implement fallback.
    HandlerClosure_t fallback_handler; 
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




HandlerReturnStatus_t Route_handle(Route_t* this, AppKernel_t* app, char* uri)
{
    HandlerReturnStatus_t ret;
    Route_t* subroute = NULL;
    
    ret = Route_handleThis(this,app);
    if(ret != HANDLER_CONTINUE)
        return HADNLER_HANDLED;

    
    
    
    //find the first matching subroute, consume the uri string and continue
    int len = vector_lenght(this->subroutes);
    for(int i= 0; i<len; i++)
    {
        subroute = vector_at(this->subroutes,i);
        
        //if subroute matches stop
        if( strlen(uri)>=strlen(subroute->path)
            && strncmp(subroute->path, uri, strlen(subroute->path))!=0
          )
        {
            //consume the uri string
            uri += strlen(subroute->path);
            ret =  Route_handle(subroute, app, uri);
            
            if(ret == HANDLER_NOT_FOUND)
                // Means that there was no fallback in the subroutes, this 
                // tells us that we have to call it now.
                subroute = NULL;
                
            
            else
                assert(ret == HANDLER_HANDLED);
                //continue by making sure that this is correct.
                //possibly refactor
            break;
        }
    }
    
    if(subroute == NULL)
    {
        if(this->fallback_handler == NULL)
            return HANDLER_NOT_FOUND;
        
        (this->fallback_handler)(app);
    }
    
    
    return HANDLER_HANDLED;
}



HandlerReturnStatus_t Route_handleThis(Route_t* this, AppKernel_t* app)
{
    return (*this->handler)(app);
}



void Route_addSubroute(Route_t* this, Route_t* other_route)
{
    vector_push(this->subroutes,other_route);
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
