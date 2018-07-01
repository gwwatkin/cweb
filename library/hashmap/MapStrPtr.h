#ifndef __HASHMAP_H__
#define __HASHMAP_H__

/*
 * Most of this module comes from Pete Warden's repo:
 * https://github.com/petewarden/c_hashmap
 * 
 * Types have been slightly changed and there are some new functions
 * written by George Watkins, to better suite the needs of the project.
 *  
 * The original commment follows.
 */

/*
 * Generic hashmap manipulation functions
 *
 * Originally by Elliot C Back - http://elliottback.com/wp/hashmap-implementation-in-c/
 *
 * Modified by Pete Warden to fix a serious performance problem, support strings as keys
 * and removed thread synchronization - http://petewarden.typepad.com
 */

#define MAP_MISSING -3  /* No such element */
#define MAP_FULL -2 	/* Hashmap is full */
#define MAP_OMEM -1 	/* Out of Memory */
#define MAP_OK 0 	    /* OK */


/*
 * PFany is a pointer to a function that can take two void * arguments
 * and return an integer. Returns status code..
 * 
 */
typedef int (*PFany)(void *, void *);

/*
 * MapStrPtr_t * is a pointer to an internally maintained data structure.
 * Clients of this package do not need to know how hashmaps are
 * represented.  They see and manipulate only MapStrPtr_t *'s.
 */
typedef void MapStrPtr_t;

/*
 * Return an empty hashmap. Returns NULL if empty.
*/
extern MapStrPtr_t* MapStrPtr_new();

/*
 * Iteratively call f with argument (item, data) for
 * each element data in the hashmap. The function must
 * return a map status code. If it returns anything other
 * than MAP_OK the traversal is terminated. f must
 * not reenter any hashmap functions, or deadlock may arise.
 */
extern int MapStrPtr_iterate(MapStrPtr_t* in, PFany f, void * item);

/*
 * Add an element to the hashmap. Return MAP_OK or MAP_OMEM.
 */
extern int MapStrPtr_put(MapStrPtr_t* in, char* key, void * value);

/*
 * Get an element from the hashmap. Return MAP_OK or MAP_MISSING.
 */
extern int MapStrPtr_get(MapStrPtr_t* in, char* key, void * *arg);

/*
 * Remove an element from the hashmap. Return MAP_OK or MAP_MISSING.
 */
extern int MapStrPtr_remove(MapStrPtr_t* in, char* key);

/*
 * Get any element. Return MAP_OK or MAP_MISSING.
 * remove - should the element be removed from the hashmap
 * TODO find out whhy this is missing
 */
// extern int MapStrPtr_get_one(MapStrPtr_t * in, void * *arg, int remove);

/*
 * Free the hashmap
 */
extern void MapStrPtr_free(MapStrPtr_t* in);

/*
 * Get the current size of a hashmap
 */
extern int MapStrPtr_length(MapStrPtr_t* in);

/*
 * Get a list of pointers to key strings, it's terminated by a null pointer
 * TODO use vector
 */
extern char** MapStrPtr_keys(MapStrPtr_t* in);

#endif // __HASHMAP_H__ 
