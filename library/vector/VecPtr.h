#ifndef VECTOR_H__
#define VECTOR_H__


/**
 * A simple resizeable vector implentation
 * 
 * NOTE: memory has to be managed
 * 
 * TODO write docs
 */


typedef struct VecPtr_ {
    void** data;
    int size;
    int count;
} VecPtr_t;

VecPtr_t* VecPtr_new();

int VecPtr_lenght(VecPtr_t*);

void VecPtr_add(VecPtr_t*, void*);

void VecPtr_set(VecPtr_t*, int, void*);

void *VecPtr_get(VecPtr_t*, int);

void VecPtr_remove(VecPtr_t*, int);

void VecPtr_free(VecPtr_t*);

#endif 
 
