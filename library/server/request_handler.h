#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <stdlib.h>

#include "../hashmap/MapStrStr.h" //used to store generic headers of a request


    
   /*
    * +------------------------------------------------------------------------
    * | Processed requests type
    * |------------------------------------------------------------------------
    * | this the data structure (with all the annexed types) that is used to
    * | encode the information once the request has been parsed.
    * |
    * 
    */ 

typedef enum  
{   
    UNDEFINED=-1,
    GET,
    HEAD,
    POST,
    PUT,
    PATCH,
    DELETE,
    OPTIONS,
} Method;

char * Method_show(Method);





typedef struct
{
    Method method;
    char * protocol;
    char * url;
    MapStrStr_t* plain_headers;
    
} Request;


Request * Request_new();

void Request_free(Request* r);

void Request_print(Request* r);







   /*
    * +------------------------------------------------------------------------
    * | Main requests handling method
    * |------------------------------------------------------------------------
    * |All requests go through this function
    * |
    * 
    */ 

void * request_handle(void * int_live_connection);



   /*
    * +------------------------------------------------------------------------
    * | Request Parsing
    * |------------------------------------------------------------------------
    * |These functions take a file descriptor of a connection (with the first 
    * |line parsed to determine the request type) and return a request object
    * |ready to be passed to our application
    * |
    * 
    */ 

   
   
   
   
/**
 * Used to determine the type of the request
 * @return 1 on success -1 on error.
 */
int Request_parseFirstLine(Request* r,char * line);


/**
 * Read a line and if its valid put it into the request field
 * @return 1 if its a header line 0 if it's a blank line -1 on error.
 * 
 */
int Request_parseHeaderLine(Request* r,char * line); 
   
   
   
   
   
   
   
   
   
   /*
    * +------------------------------------------------------------------------
    * | Cookie
    * |------------------------------------------------------------------------
    * | A simple web cookie
    * |
    */ 
    
    
typedef struct 
{
    char * key;
    char * value;
} Cookie;
    
    

#endif
