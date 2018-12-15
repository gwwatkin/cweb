#pragma once



#include <stdio.h>
#include <string.h>

#include <cJSON.h>

#include "../server/Route.h"
#include "../utils.h"


/**
 * TODO
 * This file works by using buffers that are larger than reasonable user input.
 * Proper bounds checking is necessary. (Possibly make a sprintf variant
 * that takes care of allocating memory)
 */


static const char* PATH_TOKEN_FIELD_NAME="path_token";
static const char* METHOD_FIELD_NAME="method";
static const char* HANDLER_FIELD_NAME="handler";
static const char* FALLBACK_HANDLER_FIELD_NAME="fallback_handler";
static const char* SUBROUTES_FIELD_NAME="subroutes";






static const char* OUTPUT_BODY=
"/** BEGIN generated using RouteParser_generateRoutes */\n\n\
/**\n\
 * Remember to free the route \n\
 */\n\
Route_t* GeneratedRoutes_get()\n\
{\
\n\
%s\
\n\
\treturn __aux_root_0;\n\
}\n\
/** END generated using RouteParser_generateRoutes */\n"; 



/**
 * Used by json2route
 */
static const char* ROUTE_CONSTRUCTOR_BODY = "\tRoute_t* __aux_root_%d = Route_new(\"%s\",%s,%s,%s);\n%s%s";
static const char* ROUTE_APPEND_TO_PARENT = "\tRoute_addSubroute(__aux_root_%d,__aux_root_%d);\n";


static int MAX_JSON_SIZE = 1048576>>1;// 0.5 MiB



static char* json2route(const cJSON*, int, int);


/**
 * Take a route json config file and turn it into a C file that generates
 * the routes.
 * 
 * allocates the returned string.
 * 
 * null characters break it
 */
char* RouteParser_generateRoutes(const char* json)
{
    char* out;
    
    if(2*strlen(json)>MAX_JSON_SIZE)
        return NULL; 
    
    cJSON* parsed_route = cJSON_Parse(json);
    
    if(parsed_route == NULL)
        out = NULL;
    else
    {
        char* compliled_routes_body = json2route(parsed_route,0,0);
        out = malloc((MAX_JSON_SIZE)*sizeof(char));
        
        sprintf(
            out,
            OUTPUT_BODY,
            compliled_routes_body
        );
        
        free(compliled_routes_body);
    }
        
    cJSON_Delete(parsed_route);
    return out;
}



static char * json2route(const cJSON* json, int current_route_suffix, int parent_suffix)
{

    
    // Get the data for the current root
    cJSON* path_token = cJSON_GetObjectItemCaseSensitive(json,PATH_TOKEN_FIELD_NAME);
    cJSON* method = cJSON_GetObjectItemCaseSensitive(json,METHOD_FIELD_NAME);
    cJSON* handler = cJSON_GetObjectItemCaseSensitive(json,HANDLER_FIELD_NAME);
    cJSON* fallback_handler = cJSON_GetObjectItemCaseSensitive(json,FALLBACK_HANDLER_FIELD_NAME);
    cJSON* subroutes = cJSON_GetObjectItemCaseSensitive(json,SUBROUTES_FIELD_NAME);
    
    
    
    // construct the subroutes
    char* substrings_body =  malloc((MAX_JSON_SIZE)*sizeof(char));
    substrings_body[0] = '\0';
    int i=1;
    cJSON* subroute;
    cJSON_ArrayForEach(subroute,subroutes)
    {
        char* compiled_subroute = json2route(subroute,current_route_suffix+i,current_route_suffix);
        strcat(substrings_body,compiled_subroute);
        free(compiled_subroute);
        i++;
    }
    
    
    // subroutes need to be appended to the  to their parent
    char* append_to_parent_route = malloc((MAX_JSON_SIZE)*sizeof(char));
    if(current_route_suffix>0) // The route nod is not appended to anything
        sprintf(
            append_to_parent_route,
            ROUTE_APPEND_TO_PARENT,
            parent_suffix,
            current_route_suffix
        ); 
    else
        strcpy(append_to_parent_route,"");
    
    
    
    // Put everything together

    char* buffer = malloc((MAX_JSON_SIZE)*sizeof(char));
    
    sprintf(
        buffer,
        ROUTE_CONSTRUCTOR_BODY,
        current_route_suffix,
        cJSON_GetStringValue(path_token),
        cJSON_GetStringValue(method),
        cJSON_GetStringValue(handler),
        cJSON_GetStringValue(fallback_handler),
        substrings_body,
        append_to_parent_route
    );
    
    free(append_to_parent_route);
    free(substrings_body);
    
    return buffer;
}















