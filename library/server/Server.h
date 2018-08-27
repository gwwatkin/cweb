#pragma once

#include "Route.h" 
#include "Request.h"
#include "Response.h"
#include "AppKernel.h"


typedef struct _Server_t Server_t;


typedef void EntryPointArgs_t;

typedef void (*EntryPointClosure_t)(EntryPointArgs_t*, Request_t*,Response_t*);


Server_t* Server_new(
    char* hostname,
    char* port
);

void Server_setEntryPoint(
    Server_t* this,
    EntryPointClosure_t entry_point,
    EntryPointArgs_t* entry_point_args);

void Server_listen(Server_t* this);

void Server_free(Server_t* this);

