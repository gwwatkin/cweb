#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


#include "../library/hashmap/MapStrStr.h"
#include "../library/vector/VecPtr.h"

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




int MapStrStr_unitTests()
{
    
    pretty_title("Testing MapStrStr");
    
    printf("Creating a MapStrStr\n");
    MapStrStr_t* m = MapStrStr_new();
    
    
    printf("Putting an element in a MapStrStr\n");
    MapStrStr_put(m,"a","my item");
    
    
    printf("Putting an element in a MapStrStr with an existing key\n");
    MapStrStr_put(m,"a","my suplicate item");
    
    printf("Putting an element in a MapStrStr\n");
    MapStrStr_put(m,"remove me","my item 2");
    
    
    printf("Getting an element from a MapStrStr:\n");
    char* s = MapStrStr_get(m,"a");
    printf("%s\n",s);
    free(s);
    
    printf("Getting a missing element from a MapStrStr\n");
    char* d = MapStrStr_get(m,"z");
    if(d)return 1;
    
//     printf("Getting a random element from a MapStrStr:\n");
//     s = MapStrStr_get_one(m,0);
//     printf("%s\n",s);
    
    
    
    printf("Getting a list of keys:\n");
    VecPtr_t* keys = MapStrStr_refsToKeys(m);
    
    printf("[");
    for(int i=0;i<VecPtr_lenght(keys);i++)
        printf("%s,", (char*) VecPtr_at(keys,i));
    printf("]\n");
    
    VecPtr_free(keys);
    
    
    printf("Removing an element from a MapStrStr\n");
    MapStrStr_delete(m,"remove me");
    d = MapStrStr_get(m,"remove me");
    if(d)return 1;
    free(d);
    
    printf("Freeing a MapStrStr\n");
    MapStrStr_freeAll(m);
    
    return 0;
    
}



int VecPtr_unitTests()
{
    
    return 0;
}



int main(){
    
    printf("\"ABC\" has length %i\n",strlen("ABC"));
    
    return MapStrStr_unitTests();
    
    
    pretty_title("Done with tests");
    
}




