#include "Path.h"

#include <stdlib.h>
#include <string.h>

#include "vector/vector.h"

struct _Path_t{
    /*
     * Nodes are stored backwards so largest index is the leftmost one.
     * This way the path can be efficently consumed from left to right.
     */
    vector_t* tokens;
};

/**
 * All generated strings need to be freed.
 */
void token_split(char* path, vector_t* out)
{
    
    if(strcmp(path,"")==0)
        return;
    
    if(*path=='/')
    {
        token_split(path+1,out);
        return;
    }
    
    char* end_tok = path;
    
    while(*end_tok!='/' && *end_tok!='\0')
        end_tok++;
    
    //abc\0
    
    unsigned len = end_tok-path;   //excludes the terminating character
    
    char* new_str = calloc(len+1, sizeof(char));
    memcpy(new_str, path, len*sizeof(char));
    
    vector_push(out,new_str);
    
    token_split(end_tok,out);
    
    //Resume here by testing this function and implementing Path_fromString.
    //and then continue implementing the resto of this class
    
}


/**
 * TODO make sure that there are no null characters except for the terminating
 * one
 */
Path_t * Path_fromString(char* path)
{
    Path_t* this = malloc(sizeof(Path_t));
    
    vector_t* toks = vector_new();
    
    token_split(path,toks);
    
    this->tokens = vector_new();
    
    // reverse toks and put it into 
    // [...]
    
    vector_free(toks);
    return this;
}



int Path_consume(Path_t* this, char* token)
{
    
    return 1;
}


