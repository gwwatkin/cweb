#pragma once

#include "Route.h" 
#include "Request.h"
#include "Response.h"



typedef struct _Server_t Server_t;


typedef Response_t* (*EntryPointClosure_t)(Request_t*);


Server_t* Server_new(char* host, char* port, EntryPointClosure_t entry_point);

void Server_listen(Server_t* this);

void ServerFree(Server_t* this);

