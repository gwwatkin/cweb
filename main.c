#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vendor/onion/src/onion/onion.h"
#include "vendor/onion/src/onion/request.h"


#include "library/server/AppKernel.h"
#include "library/server/Request.h"
#include "library/server/Response.h"

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





int main_handler(void *private_data, onion_request *request, onion_response *response)
{
    const char* path = onion_request_get_path(request);
    
    printf("\e[32m[main_handler]\e[0m Starting AppKernel\n");
    AppKernel_t* app = AppKernel_new(); 
    
    
    onion_response_printf(response,"%s\n",path);
    
    
    
    AppKernel_free(app); 
    printf("\e[32m[main_handler]\e[0m Terminating AppKernel\n");
    
    return OCS_PROCESSED;
}




int main(int argc,char *argv[])
{
    onion* o = onion_new(O_POOL);
    onion_set_hostname(o, HOSTNAME);
    onion_set_port(o,PORT);
    
    
    
    
    onion_set_root_handler(
        o,
        onion_handler_new(
            (void *)main_handler,
                NULL,
                NULL 
            )
    );
    
    

    onion_listen(o);
    
    onion_free(o);
    
}





