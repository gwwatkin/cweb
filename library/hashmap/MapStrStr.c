#include <string.h>
#include <stdlib.h>

#include "MapStrStr.h"

#include "Hashmap.h"

MapStrStr_t* MapStrStr_new()
{
    return Hashmap_new();
}

int MapStrStr_put(MapStrStr_t* in, char* key, char* value)
{
    char* new_val = strdup(value);
    
    return Hashmap_put(in,key,(void*) new_val);
}


char* MapStrStr_get(MapStrStr_t* in, char* key)
{
    char * val = (char*) Hashmap_at(in,key);
    if(val) 
        return strdup(val);
    
    else 
        return NULL;
}


char* MapStrStr_at(MapStrStr_t* in, char* key)
{
    return (char*) Hashmap_at(in,key);
    
}




/*
 * Remove an element from the hashmap. Return MAP_OK or MAP_MISSING.
 * 
 * Automatically free the value as well
 */
int MapStrStr_delete(MapStrStr_t* in, char* key)
{   
    free(Hashmap_at(in,key));
    
    return Hashmap_remove(in,key);
}

/*
 * Get any element. Return MAP_OK or MAP_MISSING.
 * remove - should the element be removed from the hashmap
 */
// char * MapStrStr_get_one(MapStrStr_t* in, int remove)
// {
//     char* arg;
//     
//     int ret = Hashmap_get_one(in,(void **) &arg,remove);
//     
//     if(ret == MAP_OK)
//         return strdup(arg);
//     
//     return NULL;
// }

/*
 * Free the hashmap
 */
void MapStrStr_freeAll(MapStrStr_t* in)
{
    Hashmap_freeAll(in);
}


/*
 * Get the current size of a hashmap
 */
int MapStrStr_length(MapStrStr_t* in)
{
    return Hashmap_length(in);
}


VecPtr_t * MapStrStr_refsToKeys(MapStrStr_t* in)
{
    return Hashmap_refsToKeys(in);
}


VecPtr_t* MapStrStr_keys(MapStrStr_t* in)
{
    return Hashmap_keys(in);
}
