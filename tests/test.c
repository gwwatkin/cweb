#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../library/utils.h"



#include "../library/hashmap/MapStrStr.h"
#include "../library/vector/vector.h"
#include "../library/server/Route.h"





HandlerReturnStatus_t testHandler1(AppKernel_t* app)
{
    printf("testHandler1 has been called\n");
    
    return HANDLER_CONTINUE;
}



int Route_unitTests()
{
    pretty_title("Route Unit tests:\n");
    
    
    
    
    printf("Creating a Route.\n");
    Route_t* root = Route_new("/",GET,"index",&testHandler1);
    
    
    Route_t* a = Route_new("home",GET,"index",&testHandler1);
    
    Route_addSubroute(root,a);
    
    printf("Printing it:\n");
    Route_dump(root,0);

    
    
    printf("Creating a kernel.\n");
    AppKernel_t* app = AppKernel_new();
    
    printf("Running the handler.\n");
    Route_handle(root,app);
    
    printf("Freing the kernel.\n");
    AppKernel_free(app);
    
    
    
    printf("Freeing the route.\n");
    Route_free(root);

    return 1;
}







int main(){
    
    
    Route_unitTests();
    
    
    pretty_title("Done with tests");
    
}


/*
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
    vector_t* keys = MapStrStr_refsToKeys(m);
    
    printf("[");
    for(int i=0;i<vector_lenght(keys);i++)
        printf("%s,", (char*) vector_at(keys,i));
    printf("]\n");
    
    vector_free(keys);
    
    
    printf("Removing an element from a MapStrStr\n");
    MapStrStr_delete(m,"remove me");
    d = MapStrStr_get(m,"remove me");
    if(d)return 1;
    free(d);
    
    printf("Freeing a MapStrStr\n");
    MapStrStr_freeAll(m);
    
    return 0;
    
}*/
