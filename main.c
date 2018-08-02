#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <onion/onion.h>


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



#define PORT "3000"

#define HOSTNAME "0.0.0.0"


int simple_response_handler(void *private_data, onion_request *request, onion_response *response)
{
    
    onion_response_printf(response,"hi");
    
    
    return OCS_PROCESSED;
}




int main(int argc,char *argv[])
{
    onion* server = onion_new(O_POOL);
    onion_set_hostname(server, HOSTNAME);
    onion_set_port(server,PORT);
    
    
    onion_set_root_handler(
        server,
        onion_handler_new((void *)simple_response_handler,NULL,NULL)
    );
    
    
    onion_listen(server);
    onion_free(server);
    
}





