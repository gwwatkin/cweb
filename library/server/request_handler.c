#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "request_handler.h"
#include "../utils.h"



#define MAX_HEADER_LINE_LENGHT 8190 //same as apache 2.3


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
    
    
    
    
    /*
    * +------------------------------------------------------------------------
    * | Parse Request headers
    * |------------------------------------------------------------------------
    * | Read line by line the request as file and compose r->plain_headers
    * |
    * 
    */ 

    
    
    //buffer into which keep track of each line
    char line[MAX_HEADER_LINE_LENGHT+1];
    line[MAX_HEADER_LINE_LENGHT] = '\0';
    
    fgets(line,MAX_HEADER_LINE_LENGHT,reader);
    
    printf("Parsing the first line of the request\n");

    Request_parseFirstLine(r,line);

    
    printf("Starting to parse headers\n");
    
    // use this flags to stop when we hit a double null line
    char previous_was_null = 0;
    char current_is_null = 0;
    
    while(!(previous_was_null && current_is_null))
    {
        previous_was_null = current_is_null;    
        
        printf("Getting a line...\n");
        fgets(line,MAX_HEADER_LINE_LENGHT,reader);
        
        if(feof(reader))
        {
            printf("Warning: eof in header\n");
            goto eof;
        }
        
        //discard the line ending
        int len = strlen(line);
        assert(line[len-1]=='\n');
        assert(line[len-2]=='\r');
        char* clean_line = str_nullToSpace(line,len-2);
        
        
        
        //parse the line
        printf("parsing it:\n%s\n",clean_line);
        current_is_null = !Request_parseHeaderLine(r,clean_line);
       
    }
    printf("Successfully found end of head\n");
    
    
    /*
    * +------------------------------------------------------------------------
    * | Parse Request body
    * |------------------------------------------------------------------------
    * | What we do here depends on the method of the request.
    * |
    * 
    */ 
    
    switch(r->method)
    {
        case POST:
            printf("Reading a POST request's body:\n");
            
            //dump the request
            char buffer[1024];
            
            while(fscanf(reader,"%s",buffer)!=EOF)
                printf("%s",buffer);
                
            break;
        
        //there is no body or we don't know how to read it
        case GET:
        case HEAD:
        case DELETE:
        default:
            goto eof;
    }
    
    
    
    /*
    * +------------------------------------------------------------------------
    * | Finalize
    * |------------------------------------------------------------------------
    * |
    * 
    */ 
    
    //if we are here it means that the content of the request has been exausted
    eof:
    
    
    
    printf("Printing the request\n");
    
    Request_print(r);
    
    printf("Freeing the request\n");
    
    Request_free(r);

    printf("Closing the file\n");
    
    fclose(reader);
    
    
    return NULL;



    error:
    
    printf("Finalizing environment after an error.\n");
    
    printf("Freeing the request\n");
    
    Request_free(r);

    printf("Closing the file\n");
    
    fclose(reader);
    
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
        
        //TODO add more methods
    else
        r->method = UNDEFINED;

    r->protocol = protocol;
    r->url = url;

    return 1;
}



int Request_parseHeaderLine(Request* r, char* line)
{   
   if(line[0]=='\0')
       return 0;
    
    char* colon_location = strchr(line,':');
    if(colon_location==NULL)
        return -1;
   
    //separate the field name from the value
    *(colon_location) = '\0';
    
   
    char* field_name = line;
    char* field_value = colon_location+2;//skip the blank space
    assert(*(colon_location+1) == ' ');
    
    
    MapStrStr_put(r->plain_headers,field_name,field_value);
    
    
    // restore the string
    *(colon_location) = ':';
   
    return 1;
}






Request * Request_new(){
    
    Request * r = malloc(sizeof(Request));
    
    r->method = UNDEFINED;
    r->protocol = NULL;
    r->url = NULL;
    r->plain_headers = MapStrStr_new();
    
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
    
    printf("Head:\n");
    
    MapStrStr_print(r->plain_headers);
    
}


char * Method_show(Method m)
{
    char *  out = malloc(sizeof(char)*32);
    
    switch(m){
        case GET:
            return strcpy(out,"GET"); 
        case HEAD:
            return strcpy(out,"HEAD");   
        case POST:
           return strcpy(out,"POST"); 
        case PUT:
           return strcpy(out,"PUT"); 
        case PATCH:
           return strcpy(out,"PATCH"); 
        case DELETE:
           return strcpy(out,"DELETE");
        case OPTIONS:
           return strcpy(out,"OPTIONS"); 
        default:
          return strcpy(out,"NOT YET SUPPORTED");   
    }
    
}




