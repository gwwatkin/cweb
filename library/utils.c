#include <stdlib.h>
#include <string.h>

void str_replace(char * str, int len,char old, char new)
{
    for(int i=0; i<len;i++)
        if(str[i]==old)
            str[i]=new;
    
}


char* str_nullToSpace(char * str, int len)
{
    char* out = malloc(sizeof(char)*(len+1));
    
    strncpy(out,str,len);
    out[len] = '\0';
    
    str_replace(out,len,'\0',' ');
    
    return out;
}


void str_cleanNewline(char* line)
{
    int len = strlen(line);
    if(len && line[len-1]=='\r')
        line[len-1] = '\0';
    
}
