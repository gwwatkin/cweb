#ifndef MAPSTRSTR_H
#define MAPSTRSTR_H

#include "../vector/VecPtr.h"

typedef void MapStrStr_t;


/**
 * A string to string map. Once a string is put into it, a copy is stored and
 * managed internally.
 */

/*
 * Constructor
*/
MapStrStr_t* MapStrStr_new();

/*
 * Add an element to the hashmap. The value and the key are kept internally
 * Return MAP_OK or MAP_OMEM.
 */
int MapStrStr_put(MapStrStr_t* in, char* key, char* value);

/*
 * Get an element from the hashmap. (the returned value is newly allocated)
 */
char*  MapStrStr_get(MapStrStr_t* in, char* key);


/*
 * Get a reference to the string pointed to by the item at position 'key'.
 */
char*  MapStrStr_at(MapStrStr_t* in, char* key);


/*
 * Remove an element from the hashmap. Return MAP_OK or MAP_MISSING.
 * Frees the string after removing it
 */
int MapStrStr_delete(MapStrStr_t* in, char* key);

/*
 * Get any element. Return MAP_OK or MAP_MISSING.
 * remove - should the element be removed from the hashmap
 */
// char* MapStrStr_get_one(MapStrStr_t* in, int remove);

/**
 * Free the hashmap and make all of the contents disappear
 */
void MapStrStr_freeAll(MapStrStr_t* in);


/*
 * Get the current size of a hashmap
 */
int MapStrStr_length(MapStrStr_t* in);



/**
 * Get a vector containing all the strings used as keys in the map
 */
VecPtr_t* MapStrStr_key(MapStrStr_t* in);


/*
 * Get a vector containg all the defined keys in the hashmap.
 * 
 * The pointers returned are those that point directly to the key strings.
 * WARNING editing them will break the map, use for read only.
 */
VecPtr_t* MapStrStr_refsToKeys(MapStrStr_t* in);


/*
 * Print to screen the contents of a hashmap (usefull for debug)
 */
void MapStrStr_print(MapStrStr_t* in);



#endif // MAPSTRSTR_H 
