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
 */


typedef struct _Hashmap_element{
    char* key;
    int in_use;
    void* data;
} Hashmap_element;

typedef struct _Hashmap_t{
    int table_size;
    int size;
    Hashmap_element *data;
} Hashmap_t;





#include "../vector/VecPtr.h"



#define MAP_MISSING -3  /* No such element */
#define MAP_FULL -2 	/* Hashmap is full */
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
Hashmap_t* Hashmap_new();

/*
 * Iteratively call f with argument (item, data) for
 * each element data in the hashmap. The function must
 * return a map status code. If it returns anything other
 * than MAP_OK the traversal is terminated. f must
 * not reenter any hashmap functions, or deadlock may arise.
 */
int Hashmap_iterate(Hashmap_t* m, PFany f, void* item);

/*
 * Add an element to the hashmap. Return MAP_OK or MAP_OMEM.
 * Key is duplicated before use
 */
int Hashmap_put(Hashmap_t* m, char* key, void * value);

/*
 * Get an element from the hashmap. Return MAP_OK or MAP_MISSING.
 */
void* Hashmap_at(Hashmap_t* m, char* key);
 
 
 /*
 * Remove an element from the hashmap.
 * Return MAP_OK or MAP_MISSING.
 * 
 * No resizing ever occurs.
 */
 int Hashmap_remove(Hashmap_t* m, char* key);
 
/*
 * Get any element. Return MAP_OK or MAP_MISSING.
 * remove - should the element be removed from the hashmap
 * TODO find out whhy this is missing
 */
/* int Hashmap_get_one(Hashmap_t * in, void * *arg, int remove); */


void Hashmap_free(Hashmap_t* m);



/*
 * 
 * Same as Hashmap_free, but it also calls a free on the values of the hashmap
 * before freeing the hashmap.
 */
void Hashmap_freeAll(Hashmap_t* m);


/*
 * Count the number of items in the hashmap.
 */
int Hashmap_length(Hashmap_t* m);

/* 
 * Get an array of pointers to key strings.
 * The strings are newly allocated.
 */
VecPtr_t* Hashmap_keys(Hashmap_t* m);


/* 
 * Get an array of pointers to key strings.
 * The strings are not newly allocated. Good for iterating and read only purposes.
 * 
 * WARNING editing the strings will break the hashmap.
 */
VecPtr_t*  Hashmap_refsToKeys(Hashmap_t* m);


#endif // __HASHMAP_H__ 
