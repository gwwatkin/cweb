#pragma once

#include "Server.h"
#include "AppKernel.h"
#include "Route.h"



typedef struct _App_t App_t;


App_t* App_new(AppKernel_t* kernel,int free_kernel_flag);

/**
 * Launch a web app that can handle requests using the given server and the
 * given Routing table.
 */
void App_serve(App_t* this, Server_t* server, Route_t* root);


void App_free(App_t* this);
