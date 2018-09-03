#pragma once


typedef struct _Path_t Path_t;


Path_t* Path_fromString(const char* path);


/**
 * If the given string matches one path token, consume that token and return 1,
 * otherwise just return 0.
 */
int Path_tryToConsume(Path_t* this, const char* token);

void Path_free(Path_t* this);
