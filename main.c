#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "library/server/AppKernel.h"
#include "library/server/App.h"
#include "library/server/Request.h"
#include "library/server/Response.h"
#include "library/server/Server.h"

/*
 * 
 * +_-_-_-_-_-_-_-_-_-_+
 * || __       __ __  ||
 * ||/   |   /|__ |_' ||
 * ||\__ |/|/ |__ |_' ||
 * +_-_-_-_-_-_-_-_-_-_+
 *  
 * A framework for writing webapps in C.
 * 
 */




#define HOSTNAME "0.0.0.0"


HandlerReturnStatus_t say_hello(AppKernel_t*k)
{
    printf("say_hello called\n");
    
    return HANDLER_HANDLED;
}



Route_t* make_dummy_root()
{
    Route_t* root = Route_new("",GET,"say_hello",say_hello,NULL);
    
    return root;
}
    
    
int main (int argc,char *argv[])
{
    if(argc <2)
    {
        printf("Please specify a port\n");
        return 1;
    }
        
    char* port = argv[1];
    
    Server_t* server= Server_new(HOSTNAME,port);
    
    AppKernel_t* kernel = AppKernel_new();
    
    App_t* app = App_new(kernel,0);
    
    Route_t* root = make_dummy_root();
    
    App_serve(app,server,root);
    
    
    Server_free(server);
    AppKernel_free(kernel);
    App_free(app);
    Route_free(root);
    
    
    return 0;
}





