#pragma once


/**
 * A simple resizeable vector implentation
 * 
 * NOTE: memory has to be managed
 * 
 * TODO write docs
 */


typedef struct vector_ {
    void** data;
    int size;
    int count;
} vector_t;

vector_t* vector_new();

int vector_lenght(vector_t*);

void vector_push(vector_t*, void*);

void* vector_pop(vector_t*);

void vector_set(vector_t*, int, void*);

void *vector_at(vector_t*, int);

void vector_remove(vector_t*, int);

void vector_free(vector_t*);

/**
 * Same as vector_free, but also cals free on all of its items.
 */


/* A simple macro for the very common array pattern
 * NOTE: make sure to declare the identifiers before hand
 */
#define foreach(vector,index,value)         \
for(                                        \
    value = vector_at(vector,index=0);      \
    index< vector_lenght(vector);           \
    value = vector_at(vector,++index)       \
)







