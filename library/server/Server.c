#include "Server.h"

#include <stdlib.h>
#include <string.h>


#include "../../vendor/onion/src/onion/onion.h"
#include "../../vendor/onion/src/onion/request.h"




struct _Server_t {
    
    char* port;
    char* hostname;
    
    EntryPointClosure_t entry_point;
    
};



// Server_t* Server_new(char* host, char* port, EntryPointClosure_t entry_point)
// {
//     Server_t* server = malloc(sizeof(Server_t));
//     
//     server->port = strdup(port);
//     server->hostname = strdup(hostname);
//     
//     return server;
// }
// 
// 
// void ServerFree(Server_t* this)
// {
//     free(this->port);
//     
//     free(this->hostname);
//     
//     free(this);
// }




static onion_connection_status runEntryPoint_(
    void* server,
    onion_request* req,
    onion_response* resp);

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
    onion_request* req,
    onion_response* resp)
{
    Server_t* this = (Server_t*) server;
    
    //convert an onion request to a Request type;
    
    //call the entry entry
    
    //convert the Response to an onion response
    
    //write it out.
    
    return OCS_PROCESSED;
}




