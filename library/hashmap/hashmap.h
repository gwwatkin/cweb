#ifndef __HASHMAP_H__
#define __HASHMAP_H__

/*
 * A Simple hashmap implementation.
 * 
 * The hash table mechanism is based on Pete Warden's.
 * https://github.com/petewarden/c_hashmap
 * 
 * TODO make thread safe
 * 
 */







/*
 * This hash map uses a resizeable table with linear probing.
 * 
 * Keys are maintained internally
 */


typedef struct _hashmap_element{
    char* key;
    int in_use;
    void* data;
} hashmap_element;

typedef struct _hashmap_t{
    int table_size;
    int size;
    hashmap_element *data;
} hashmap_t;





#include "../vector/vector.h"



#define MAP_MISSING -3  /* No such element */
#define MAP_FULL -2 	/* hashmap is full */
#define MAP_OMEM -1 	/* Out of Memory */
#define MAP_OK 0 	    /* OK */




/*
 * PFany is a pointer to a function that can take two void * arguments
 * and return an integer. Returns status code.
 * 
 * Used when iterating through the table.
 */
typedef int (*PFany)(void *, void *);




/*
 * Return an empty hashmap. Returns NULL on fail.
*/
hashmap_t* hashmap_new();

/*
 * Iteratively call f with argument (item, data) for
 * each element data in the hashmap. The function must
 * return a map status code. If it returns anything other
 * than MAP_OK the traversal is terminated. f must
 * not reenter any hashmap functions, or deadlock may arise.
 */
int hashmap_iterate(hashmap_t* m, PFany f, void* item);

/*
 * Add an element to the hashmap. Return MAP_OK or MAP_OMEM.
 * Key is duplicated before use
 */
int hashmap_put(hashmap_t* m, char* key, void * value);

/*
 * Get an element from the hashmap. Return MAP_OK or MAP_MISSING.
 */
void* hashmap_at(hashmap_t* m, char* key);
 
 
 /*
 * Remove an element from the hashmap.
 * Return MAP_OK or MAP_MISSING.
 * 
 * No resizing ever occurs.
 */
 int hashmap_remove(hashmap_t* m, char* key);
 
/*
 * Get any element. Return MAP_OK or MAP_MISSING.
 * remove - should the element be removed from the hashmap
 * TODO find out whhy this is missing
 */
/* int hashmap_get_one(hashmap_t * in, void * *arg, int remove); */


void hashmap_free(hashmap_t* m);



/*
 * 
 * Same as hashmap_free, but it also calls a free on the values of the hashmap
 * before freeing the hashmap.
 */
void hashmap_freeAll(hashmap_t* m);


/*
 * Count the number of items in the hashmap.
 */
int hashmap_length(hashmap_t* m);

/* 
 * Get an array of pointers to key strings.
 * The strings are newly allocated.
 */
vector_t* hashmap_keys(hashmap_t* m);


/* 
 * Get an array of pointers to key strings.
 * The strings are not newly allocated. Good for iterating and read only purposes.
 * 
 * WARNING editing the strings will break the hashmap.
 */
vector_t*  hashmap_refsToKeys(hashmap_t* m);


#endif // __HASHMAP_H__ 
