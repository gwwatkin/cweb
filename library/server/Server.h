#pragma once

#include "Route.h" 
#include "Request.h"
#include "Response.h"



typedef struct _Server_t Server_t;


typedef void (*EntryPointClosure_t)(Request_t*,Response_t*);


Server_t* Server_new(char* hostname, char* port, EntryPointClosure_t entry_point);

void Server_listen(Server_t* this);

void Server_free(Server_t* this);

