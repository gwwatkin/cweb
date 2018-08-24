#include "Server.h"

#include <stdlib.h>
#include <string.h>


#include "../../vendor/onion/src/onion/onion.h"




struct _Server_t {
    
    char* port;
    char* hostname;
    
    EntryPointClosure_t entry_point;
    
};



Server_t* Server_new(char* hostname, char* port, EntryPointClosure_t entry_point)
{
    Server_t* server = malloc(sizeof(Server_t));
    
    server->port = strdup(port);
    server->hostname = strdup(hostname);
    server->entry_point = entry_point;
    
    return server;
}


void Server_free(Server_t* this)
{
    free(this->port);
    
    free(this->hostname);
    
    free(this);
}




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
    
    
    onion_handler* root_handler = onion_handler_new(
            &runEntryPoint_,
            this,
            NULL
    );
    
    onion_set_root_handler(o,root_handler);
    
    onion_listen(o);

    onion_free(o);
    onion_handler_free(root_handler);

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
    (*this->entry_point)(request,response);
    
    //write the response to the onion response object
    Response_writeToOnion(response,o_response);
    
    return OCS_PROCESSED;
}




