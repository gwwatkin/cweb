#pragma once

#include <onion/types.h>

typedef struct _Response_t Response_t;


Response_t* Response_new();

void Response_free(Response_t* this);

/**
 * copies the body
 */
void Response_setBody(Response_t* this, char* body,int body_size);

void Response_writeToOnion(Response_t* this, onion_response* o_response);


