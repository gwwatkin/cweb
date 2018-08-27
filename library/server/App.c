#include "App.h"
#include <stdlib.h>

struct _App_t{
    AppKernel_t* kernel;
    int free_kernel_flag;
};


struct App_EntryPointArgs
{
    Route_t* root;
    AppKernel_t* kernel;
};


/* BEGIN private methods*/



static void entry_point_for_app(
    EntryPointArgs_t* args_,
    Request_t* request,
    Response_t* response
);


/* END private methods */

App_t* App_new(AppKernel_t* kernel,int free_kernel_flag)
{
    App_t* this = malloc(sizeof(App_t));

    this->kernel = kernel;
    this->free_kernel_flag = free_kernel_flag;
    
    return this;
}



void App_serve(App_t* this, Server_t* server, Route_t* root)
{
    
    struct App_EntryPointArgs args;
    args.root = root;
    args.kernel = this->kernel;
    
    Server_setEntryPoint(server,entry_point_for_app,&args);
    Server_listen(server);
}



void App_free(App_t* this)
{
    if(this->free_kernel_flag && this->kernel)
        AppKernel_free(this->kernel);
    
    free(this);
}




/** @type EntryPointClosure_t */
static void entry_point_for_app(EntryPointArgs_t* args_,Request_t* request, Response_t* response)
{
    struct App_EntryPointArgs* args = args_;
    
    const char* uri = Request_getPath(request);
    
    // Register the request and the response in the kernel
    
    AppKernel_setService(
        args->kernel,
        "request",
        request,
        NULL
    );
    
    AppKernel_setService(
        args->kernel,
        "response",
        response,
        NULL
    );


    Route_handle(args->root,args->kernel,uri);
}
