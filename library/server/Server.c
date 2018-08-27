#include "Server.h"

#include <stdlib.h>
#include <string.h>


#include "../../vendor/onion/src/onion/onion.h"




struct _Server_t {
    
    char* port;
    char* hostname;
    
    
    
    EntryPointClosure_t entry_point;
    EntryPointArgs_t* entry_point_args;
};



Server_t* Server_new(
    char* hostname,
    char* port
)
{
    Server_t* server = malloc(sizeof(Server_t));
    
    server->port = strdup(port);
    server->hostname = strdup(hostname);
    
    return server;
}


void Server_free(Server_t* this)
{
    free(this->port);
    
    free(this->hostname);
    
    free(this);
}




void Server_setEntryPoint(Server_t* this,EntryPointClosure_t entry_point, EntryPointArgs_t* entry_point_args)
{
    this->entry_point = entry_point;
    this->entry_point_args = entry_point_args;
}



/**
 * This is a helper function that wraps the entry point.
 * It allows for the onion request and response objects to be converted to 
 * Request_t and Response_t types.
 */
static onion_connection_status runEntryPoint_(
    void* server,
    onion_request* o_request,
    onion_response* o_response
);

void Server_listen(Server_t* this)
{
    onion* o = onion_new(O_POOL);
    onion_set_hostname(o, this->hostname );
    onion_set_port(o,this->port);
    
    /*
     * The first argument is the closure and the second one what is passed
     * as the first argument to the closure
     */
    onion_handler* root_handler = onion_handler_new(
            &runEntryPoint_,
            this,
            NULL
    );
    
    //onion_free frees this handler
    onion_set_root_handler(o,root_handler);
    
    onion_listen(o);

    onion_free(o);
}




onion_connection_status runEntryPoint_(
    void* server,
    onion_request* o_request,
    onion_response* o_response)
{
    Server_t* this = (Server_t*) server;
    
    //convert an onion request to a Request type;
    Request_t* request = Request_fromOnion(o_request,1);
    Response_t* response = Response_new();
    
    //call the entry point
    (*this->entry_point)(this->entry_point_args,request,response);
    
    //write the response to the onion response object
    Response_writeToOnion(response,o_response);
    
    
    Request_free(request);
    Response_free(response);
    
    return OCS_PROCESSED;
}




