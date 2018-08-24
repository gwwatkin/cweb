#pragma once

#include "../../vendor/onion/src/onion/types.h"

typedef struct _Response_t Response_t;


Response_t* Response_new();

void Response_free();

void Response_writeToOnion(onion_response* o_response);


