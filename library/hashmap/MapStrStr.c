#include <string.h>
#include <stdlib.h>

#include "MapStrStr.h"

#include "MapStrPtr.h"

MapStrStr_t* MapStrStr_new()
{
    return MapStrPtr_new();
}

int MapStrStr_put(MapStrStr_t* in, char* key, char* value)
{
    char* new_val = strdup(value);
    char* new_key = strdup(key);
    
    return MapStrPtr_put(in,new_key,(void*) new_val);
}


char* MapStrStr_get(MapStrStr_t* in, char* key)
{
    char* arg = NULL;
    
    int ret = MapStrPtr_get(in,key,(void **) &arg);
    
    if(ret == MAP_OK)
        return strdup(arg);
    
    return NULL;
}



/*
 * Remove an element from the hashmap. Return MAP_OK or MAP_MISSING.
 * 
 * Automatically free the key/value pair
 */
int MapStrStr_delete(MapStrStr_t* in, char* key)
{   
    return MapStrPtr_delete(in,key);
}

/*
 * Get any element. Return MAP_OK or MAP_MISSING.
 * remove - should the element be removed from the hashmap
 */
// char * MapStrStr_get_one(MapStrStr_t* in, int remove)
// {
//     char* arg;
//     
//     int ret = MapStrPtr_get_one(in,(void **) &arg,remove);
//     
//     if(ret == MAP_OK)
//         return strdup(arg);
//     
//     return NULL;
// }

/*
 * Free the hashmap
 */
void MapStrStr_free(MapStrStr_t* in)
{
    return MapStrPtr_free(in);
}


void MapStrStr_freeAll(MapStrStr_t* in)
{
    VecPtr_t * keys = MapStrStr_keys(in);
    
    for(int i= 0;i<MapStrStr_length(in);i++)
    {
        //free the values string
        free( MapStrStr_get(in,VecPtr_get(keys,i)));
        
        //free the key string
        free( VecPtr_get(keys,i));
    }
        
    VecPtr_free(keys);
    
    MapStrPtr_free(in);
    
}


/*
 * Get the current size of a hashmap
 */
int MapStrStr_length(MapStrStr_t* in)
{
    return MapStrPtr_length(in);
}


//FIXME return a vector
VecPtr_t* MapStrStr_keys(MapStrStr_t* in)
{
    return MapStrPtr_keys(in);
}
