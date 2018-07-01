#ifndef VECTOR_H__
#define VECTOR_H__


typedef struct VecPtr_ {
    void** data;
    int size;
    int count;
} VecPtr_t;

void VecPtr_new(VecPtr_t*);

int VecPtr_lenght(VecPtr_t*);

void VecPtr_add(VecPtr_t*, void*);

void VecPtr_set(VecPtr_t*, int, void*);

void *VecPtr_get(VecPtr_t*, int);

void VecPtr_delete(VecPtr_t*, int);

void VecPtr_free(VecPtr_t*);

#endif 
 
