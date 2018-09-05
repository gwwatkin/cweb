#include "Path.h"

#include <stdlib.h>
#include <string.h>

#include <stdio.h>//debug

#include "vector/vector.h"

struct _Path_t{
    /*
     * path tokens are stored backwards so largest index is the leftmost one.
     * This way the path can be efficently consumed from left to right.
     * 
     * All tokens are null terminated.
     */
    vector_t* tokens;
};



/**
 * Parse a path token, return a mallocd string containing it and set the
 * memory at chars consumed to the number of chars consumed.
 */
char* path_token(const char* path,int* chars_consumed);


/**
 * Take a path in a null terminated string and put all the tokens of the path
 * in the given vector.
 * 
 * i.e.: my/long/path gives the vector:
 * ["my","long","path"] 
 * 
 * All generated strings need to be freed.
 */
void token_split(const char* path, vector_t* out);


/**
 * TODO make sure that there are no null characters except for the terminating
 * one
 */
Path_t * Path_fromString(const char* path)
{
    Path_t* this = malloc(sizeof(Path_t));
    
    
    //Generate the tokens
    vector_t* toks = vector_new();
    token_split(path,toks);
    
    
    //store them in reverse order
    this->tokens = vector_new();
    while(vector_lenght(toks))
    {
        vector_push(this->tokens,vector_pop(toks));
    }
        
    vector_free(toks);
    return this;
}



int Path_tryToConsume(Path_t* this, const char* token)
{
    //handle empty path
    if(vector_lenght(this->tokens)==0)
        return *token=='\0'; 

    
    //tokens are stored in revered order
    char* current = vector_at(this->tokens,vector_lenght(this->tokens)-1);
    
    
    printf("matching %s against %s\n",current,token);
    if(strcmp(current,token)==0)
    {
        vector_pop(this->tokens);
        free(current);
        return 1;
    }
    
    return 0;
}



void Path_free(Path_t* this)
{
    int i;
    char* token;
    
    foreach(this->tokens,i,token)
        free(token);
    
    vector_free(this->tokens);
    
    free(this);
}






void token_split(const char* path, vector_t* out)
{
    
    if(strcmp(path,"")==0)
        return;
    
    int chars_consumed = 0;
    char* token = path_token(path,&chars_consumed);
    
    const char* end_tok = path + chars_consumed;
    
    vector_push(out,token);
    
    token_split(end_tok,out);
    
}



char * path_token(const char* path, int* chars_consumed)
{
    const char* end_tok = path;
    
    while(*end_tok!='/' && *end_tok!='\0')
        end_tok++;
    
    //abc\0
    
    unsigned len = end_tok-path;   //excludes the terminating character
    
    char* new_str = calloc(len+1, sizeof(char));
    memcpy(new_str, path, len*sizeof(char));
    
    
    //if the last token was a slash we have to consume it as well
    (*chars_consumed) = *end_tok=='/' ? len+1 : len;
    return new_str;
}


