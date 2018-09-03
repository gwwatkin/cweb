#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../library/utils.h"


#include "../library/vector/vector.h"
#include "../library/server/Route.h"










void token_split(char* path, vector_t* out);




int token_split_tests()
{
    
    printf("Allocating a vector\n");
    
    vector_t* v = vector_new();
        
    char* str = "one/two//three/four/";
    
    printf("Testing this string:\n%s\n",str);
    
    token_split(str,v);
    
    printf("Was split in the following tokens:\n");
    
    char* token;
    int i;
    
    foreach(v,i,token)
        printf("\t%s\n",token);
    
    printf("Freeing its items\n");
    
    foreach(v,i,token)
        free(token);
    
    printf("Freeing the vector\n");
    
    
    vector_free(v);
    
    return 0;
}






HandlerReturnStatus_t testHandler1(AppKernel_t* app)
{
    printf("testHandler1 has been called!\n");
    
    return HANDLER_CONTINUE;
}


HandlerReturnStatus_t testHandler2(AppKernel_t* app)
{
    printf("testHandler2 has been called!\n");
    
    return HANDLER_CONTINUE;
}

HandlerReturnStatus_t testHandler3(AppKernel_t* app)
{
    printf("testHandler3 has been called!\n");
    
    return HANDLER_CONTINUE;
}


HandlerReturnStatus_t fallbackHandler1(AppKernel_t* app,HandlerReturnStatus_t status)
{
     printf("fallbackHandler1 has been called ");
     printf("with status %i\n",status);
     
     return HANDLER_HANDLED;
}



int Route_unitTests()
{
    printf("Creating a Route.\n");
    Route_t* root = Route_new("",GET,"index",&testHandler1,&fallbackHandler1);
    
    Route_t* a = Route_new("my",GET,"index",&testHandler2,NULL);
    
    Route_t* b = Route_new("path",GET,"index",&testHandler3,NULL);
    
    Route_addSubroute(a,b);
    Route_addSubroute(root,a);
    
    printf("Printing it:\n");
    Route_dump(root,0);

    
    printf("Creating a kernel.\n");
    AppKernel_t* app = AppKernel_new();
    
    printf("Running the handler.\n");
    
    Path_t*uri = Path_fromString("my/path");
    Route_handle(root,app,uri);
    
    printf("Freing the kernel.\n");
    AppKernel_free(app);
    
    
    
    printf("Freeing the route.\n");
    Route_free(root);


    return 0;
}




int vector_unitTest()
{
    printf("vector unit test:\n");
    
    vector_t* a_vec = vector_new();
    
    int some_nums[5] = {10,20,30,40,50};
    
    for(int i = 0; i<5;i++)
        vector_push(a_vec, &some_nums[i]);
    
    int i;
    int *item;
    
    foreach(a_vec,i,item)
        printf("item at %i: %i\n",i,*item);
        
        
    vector_free(a_vec);
    
    return 0;
}


int main(){
    
//     pretty_title("vector Unit tests:");
//     
//     vector_unitTest();
    
    pretty_title("token_split tests");
    
    token_split_tests();
    
    pretty_title("Route Unit tests");
    
    Route_unitTests();
    
    pretty_title("Done with tests");
    
}
