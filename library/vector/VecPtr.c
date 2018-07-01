#include <stdlib.h>
#include <string.h>

#include "VecPtr_t.h"

void VecPtr_new(VecPtr_t *v)
{
	v->data = NULL;
	v->size = 0;
	v->count = 0;
}

int VecPtr_size(VecPtr_t *v)
{
	return v->count;
}

void VecPtr_add(VecPtr_t *v, void *e)
{
	if (v->size == 0) {
		v->size = 10;
		v->data = malloc(sizeof(void*) * v->size);
		memset(v->data, '\0', sizeof(void) * v->size);
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

void VecPtr_set(VecPtr_t *v, int index, void *e)
{
	if (index >= v->count) {
		return;
	}

	v->data[index] = e;
}

void *VecPtr_get(VecPtr_t *v, int index)
{
	if (index >= v->count) {
		return NULL;
	}

	return v->data[index];
}

void VecPtr_delete(VecPtr_t *v, int index)
{
	if (index >= v->count) {
		return;
	}

	v->data[index] = NULL;

	int i, j;
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

void VecPtr_free(VecPtr_t *v)
{
	free(v->data);
}

