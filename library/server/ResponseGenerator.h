#pragma once
#include <stdio.h>


typedef struct _responseGenerator
{
    int status;
    
    FILE* output_stream;
    
} ResponseGenerator_t;



ResponseGenerator_t* ResponseGenerator_new(FILE* output_stream);

int ResponseGenerator_send(ResponseGenerator_t* rg);

void ResponseGenerator_free(ResponseGenerator_t* rg);
