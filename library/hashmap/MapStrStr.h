#ifndef MAPSTRSTR_H
#define MAPSTRSTR_H


typedef void MapStrStr_t;


/*
 * Constructor
*/
MapStrStr_t* MapStrStr_new();

/*
 * Add an element to the hashmap. Return MAP_OK or MAP_OMEM.
 */
int MapStrStr_put(MapStrStr_t* in, char* key, char* value);

/*
 * Get an element from the hashmap. Return MAP_OK or MAP_MISSING.
 */
char*  MapStrStr_get(MapStrStr_t* in, char* key);

/*
 * Remove an element from the hashmap. Return MAP_OK or MAP_MISSING.
 */
int MapStrStr_remove(MapStrStr_t* in, char* key);

/*
 * Get any element. Return MAP_OK or MAP_MISSING.
 * remove - should the element be removed from the hashmap
 */
// char* MapStrStr_get_one(MapStrStr_t* in, int remove);

/*
 * Free the hashmap
 */
void MapStrStr_free(MapStrStr_t* in);

/*
 * Get the current size of a hashmap
 */
int MapStrStr_length(MapStrStr_t* in);


/*
 * Get a vector containg all the defined keys in the hashmap
 */
char** MapStrStr_keys(MapStrStr_t* in);




#endif // MAPSTRSTR_H 
