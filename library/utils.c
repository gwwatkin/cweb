#include <stdio.h>       
#include <assert.h>
#include <string.h>

void pindent(int indent)
{
    for(int i = 0; i<indent; i++)
        putchar((int)'\t');
}


void pretty_title(char* title){
    
    //keep of the form 4*n+2 for optimal results
    const int DEFAULT_WIDTH = 54;
    
    int len = strlen(title);
    assert(len<DEFAULT_WIDTH-2);
    
    
    char tmp[DEFAULT_WIDTH-1];
    strcpy(tmp,title);
    
    if(len%2) //if len is odd then we add a blank character ad the end
    {
        strcat(tmp," ");
        len++;
    }
    
    //print the upper line
    putchar('+');
    for(int i = 0;i<DEFAULT_WIDTH-2;i++)
        putchar('-');
    putchar('+');
    putchar('\n');
    
    
    
    //print the middle line
    
    int bar_len = (DEFAULT_WIDTH - 4 - len)/2;
    
    putchar('|');
    
    for(int i = 0;i<bar_len;i++)
    {
        if(i%2)
            putchar('-');
        else
            putchar('*');
    }
    
    printf(" %s ", tmp);
    
    
    for(int i = 0;i<bar_len;i++)
    {
        if(i%2)
            putchar('*');
        else
            putchar('-');
    }
    
    
    putchar('|');
    putchar('\n');

    //print the lower line

    putchar('+');
    for(int i = 0;i<DEFAULT_WIDTH-2;i++)
        putchar('-');
    putchar('+');
    putchar('\n');
}

