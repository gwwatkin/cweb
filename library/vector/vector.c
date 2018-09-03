#include <stdlib.h>
#include <string.h>

#include "vector.h"

vector_t* vector_new()
{
    vector_t * v = malloc(sizeof(vector_t));
    
    v->data = NULL;
    v->size = 0;
    v->count = 0;
    
    return v;
}

int vector_lenght(vector_t*v)
{
    return v->count;
}

void vector_push(vector_t *v, void *e)
{
    if (v->size == 0) {
        v->size = 10;
        v->data = malloc(sizeof(void*) * v->size);
        memset(v->data, 0, sizeof(void) * v->size);
    }

    // condition to increase v->data:
    // last slot exhausted
    if (v->size == v->count) {
        v->size *= 2;
        v->data = realloc(v->data, sizeof(void*) * v->size);
    }

    v->data[v->count] = e;
    v->count++;
}


void* vector_pop(vector_t* this)
{
    size_t len = vector_lenght(this);
    
    if(!len)
        return NULL;
    
    void* item = vector_at(this,len-1);
    
    vector_remove(this,len-1);
            
    return item;
}



void vector_set(vector_t *v, int index, void *e)
{
    if (index >= v->count)
        return;

    v->data[index] = e;
}

void *vector_at(vector_t *v, int index)
{
    if (index >= v->count) {
        return NULL;
    }

    return v->data[index];
}

void vector_remove(vector_t *v, int index)
{
    if (index >= v->count) {
        return;
    }

    v->data[index] = NULL;

    int i, j;
    //TODO use realloc to improve performance
    void **newarr = (void**)malloc(sizeof(void*) * v->count * 2);
    for (i = 0, j = 0; i < v->count; i++) {
        if (v->data[i] != NULL) {
            newarr[j] = v->data[i];
            j++;
        }
    }

    free(v->data);

    v->data = newarr;
    v->count--;
}

void vector_free(vector_t *v)
{
    free(v->data);
    free(v);
}



