#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../library/string/Str.h"

/**
 * Since the testing framework relies on the Str class we have to test it
 * without it
 */
void assert_true(int assertion,int line_number,char* filename)
{
    if(!assertion)
    {
        printf("\e[31mAssertion failed at line %i in file %s\e[0m\n",line_number,filename);
        exit(1);
    }
    else
    {
        printf("\eAssertion passed at line %i in file %s\n",line_number,filename);
    }
    
}

#define ASSERT_TRUE(expr) assert_true((expr),__LINE__,__FILE__) 

int main(){
    
    


    Str_t* base = Str_dupCStr("a");
    
    // Test null charachter trimming
    ASSERT_TRUE(Str_getLen(base)==1);
    
    
    // Test appending
    Str_appendCStrN(base,"b",1);
    ASSERT_TRUE(strncmp("ab",Str_getPointerToCString(base),2)==0);
    
    Str_appendCStr(base,"c");
    ASSERT_TRUE(strncmp("abc",Str_getPointerToCString(base),3)==0);
    
    
    // Test appending to an empty string
    Str_t* empty = Str_new(0);
    Str_appendCStrN(empty,"a",1);
    ASSERT_TRUE(strncmp("a",Str_getPointerToCString(empty),1)==0);
    
    
    
    // Test reading and writing to a file
    Str_t* some_text = Str_dupCStr(
        "abcd\n\
         123\
         TEST ababtaba \
        \n"
    );
    
    
    Str_writeToFile(some_text,"autogen/test.txt");
 
    
    Str_t* read = Str_readFromFile("autogen/test.txt");
    
    ASSERT_TRUE(Str_compare(some_text,read)==0);
    
    
    Str_free(empty);
    Str_free(base);
    Str_free(some_text);
    Str_free(read);
    
    return 0;
    
}
