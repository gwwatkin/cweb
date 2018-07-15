#ifndef ARRAY_H
#define ARRAY_H

#include "vector/VecPtr.h"
#include "Value.h"

   /*
    * +------------------------------------------------------------------------
    * | JSON like Array.
    * |------------------------------------------------------------------------
    * | A simple ordered mutable array.
    * |
    * | The underlying implementation resides in VecPtr.
    * |
    * | This Array can also be used as a stack. 
    * |
    * | TODO add errors.
    * | 1) out of bounds
    * | 2) failed malloc
    * | 3) bad array
    * |  ...
    * 
    */ 


struct Array_t;
   
/* Constructor */
Array_t* Array_new();

/* Take a Value and push it into the array.
 * NOTE: this makes a copy of the Value.
 */
void Array_push(Array_t* arr);


/* pop from the back of the array, and return a pointer to the popped value, null if empty */
Value_t* Array_pop()


/* Return a copy of the Value at certain position */ 
Value_t* Array_get(Array_t* arr,int index);


/* Return a pointer to the Value at certain position */ 
Value_t* Array_at(Array_t* arr,int index);


/* Set the value at the index to some value and destroy the existing one.*/
void Array_set(Array_t* arr,int index, Value_t v);


/* Set the value at the index to a value and return the exiting one */
Value_t* Array_replace(Array_t* arr,int index, Value_t v);

/* Remove a Value from an array and destroy it. */
void Array_delete(Array_t* arr,int index);


/* Remove a Value from an array without destroing it and return a pointer to 
 * it.
 */
Value_t* Array_remove(Array_t* arr,int index);


/* Lenght of the array. */
int Array_lenght(Array_t* arr);


/* Deconstruct the array with all of its contents */
void Array_destroy(Array_t* arr);


/* A simple macro for the very common array pattern
 * NOTE: make sure to use a valid c identifier for value
 */
#define foreach(array,value)                                                         \
for(int (value)__I_i = 0,  Value_t* (value) = Array_at(array,(value)__I_i );         \
        (value)__I_i < Array_lenght(array);                                          \
        (value) = Array_at(array,++(value)__I_i)

#endif
