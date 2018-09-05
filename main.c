#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


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



HandlerReturnStatus_t fallback(AppKernel_t* k,HandlerReturnStatus_t status)
{
     printf("index called");
    
    
    Request_t* request = AppKernel_getService(k,"request");
    Response_t* response = AppKernel_getService(k,"response");
    
    printf("URI:%s\n",Request_getPath(request));
    
    char* body;
    
    if(status == HANDLER_NOT_FOUND)
        body = "404: not found";
    else
        body = "500: Some error happened"; 
    
    Response_setBody(response,body,strlen(body));
    
    
    
    
    
    return HANDLER_HANDLED;
}


HandlerReturnStatus_t index_h(AppKernel_t*k)
{
    printf("index called");
    
    
    Request_t* request = AppKernel_getService(k,"request");
    Response_t* response = AppKernel_getService(k,"response");
    
    printf("URI:%s\n",Request_getPath(request));
    
    char body[] = "this is the index";
    
    Response_setBody(response,body,strlen(body));
    
    return HANDLER_HANDLED;
}





HandlerReturnStatus_t say_hello(AppKernel_t*k)
{
    printf("say_hello called\n");
    
    Request_t* request = AppKernel_getService(k,"request");
    Response_t* response = AppKernel_getService(k,"response");
    
    printf("URI:%s\n",Request_getPath(request));
    
    char body[] = "hello";
    
    Response_setBody(response,body,strlen(body));
    

    return HANDLER_ABORT;
}



Route_t* make_dummy_root()
{
    
    Route_t* root = Route_new("",GET,"root",NULL,fallback);
    
    Route_t* hello_ = Route_new("hello",GET,"say_hello",say_hello,NULL);
    Route_t* index_ = Route_new("",GET,"index",index_h,NULL);
    
    Route_addSubroute(root,hello_);
    Route_addSubroute(root,index_);
    
    return root;
}
    
    
int main (int argc,char *argv[])
{
    if(argc <2)
    {
        printf("Please specify a port in the first argument\n");
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





