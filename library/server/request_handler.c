#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <string.h>

#include "request_handler.h"





   /*
    * +------------------------------------------------------------------------
    * | Main requests handling method
    * |------------------------------------------------------------------------
    * |All requests go through this function. It reads the headers and writes
    * |the response
    * |
    * 
    */ 


void * request_handle(void * int_live_connection){
    
     printf("Accepting request\n");
    
    /*
     * Since this function needs to be passed as an argument to the
     * pthread_create function, it's arguments and return type cannot have a
     * set type, so here we convert the argument to the correct type:
     */
    int live_connection = * ((int*) int_live_connection);
    
    FILE * reader = fdopen(live_connection,"r");
    
    
    Request * r = Request_new();
    
    
    char line[2048];
    fgets(line,2048,reader);
    
    printf("Parsing the first line of the request\n");

    Request_parseFirstLine(r,line);

    printf("Printing the request\n");
    
    Request_print(r);
    
    printf("Freeing the request\n");
    
    Request_free(r);

    return NULL;
}









int Request_parseFirstLine(Request* r, char* line)
{
    char * method = malloc(sizeof(char)*64);
    char * url = malloc(sizeof(char)*64);  
    char * protocol = malloc(sizeof(char)*64);

    sscanf(line, "%63s %63s %63s", method ,url, protocol);
    
    
    if(strcmp("GET",method) == 0)
        r->method =  GET;
    
    else if(strcmp("POST",method) == 0)
        r->method = POST;
    
    else
        r->method = UNDEFINED;

    r->protocol = protocol;
    r->url = url;

    return 1;
}






Request * Request_new(){
    
    Request * r = malloc(sizeof(Request));
    
    r->method = UNDEFINED;
    r->protocol = NULL;
    r->url = NULL;
    
    return r;
}

void Request_free(Request * r)
{
    if(!r)
        return;
    
    if(r->protocol)
        free(r->protocol);
    
    if(r->url)
        free(r->url);
    
    free(r);
}

void Request_print(Request* r)
{
    char* s =  Method_show(r->method);
    printf("Method: %s\n",s);
    free(s);
    
    if(r->protocol)
        printf("Protocol: %s\n",r->protocol);
    
    if(r->url)
        printf("Url: %s\n",r->url);

    
}


char * Method_show(Method m)
{
    char *  out = malloc(sizeof(char)*32);
    
    switch(m){
        case GET:
           return strcpy(out,"GET"); 
        case POST:
           return strcpy(out,"POST"); 
        case PUT:
           return strcpy(out,"PUT"); 
        case PATCH:
           return strcpy(out,"PATCH"); 
        case DELETE:
           return strcpy(out,"DELETE");
        case OPTIONS:
           return strcpy(out,"DELETE"); 
        default:
          return strcpy(out,"NOT YET SUPPORTED");   
    }
    
}




