#include <stdio.h>
#include <stdlib.h>

//generic socket library
#include <sys/socket.h>

//internet socket functionality
#include <netinet/in.h>

//TODO remove
//this module defines system wide constants and provides us with the read and write methods
#include <unistd.h>

//multithreading library
#include <pthread.h>




#include "./library/server/request_handler.h"



/*
 * 
 * +_-_-_-_-_-_-_-_-_-_+
 * || __       __ __  ||
 * ||/   |   /|__ |_' ||
 * ||\__ |/|/ |__ |_' ||
 * +_-_-_-_-_-_-_-_-_-_+
 *  
 * A framework for writing webapps in C.
 * 
 */



#define PORT 3000






int main(int argc,char *argv[]){
    
    
   /*
    * +------------------------------------------------------------------------
    * | First thing we create the socket
    * |------------------------------------------------------------------------
    * |
    * 
    */ 
      
    //this will be used as a handle to talk to the socket
    int sockfd;
    
    
    int success = -1;//used to detect errors while configuring the socket
    
    printf("creating socket\n");
    
    sockfd = socket( AF_INET,     // domain: IPv4 internet socket
                     SOCK_STREAM, // type: TCP (the one tipically used for http requests)
                     0            // protocol: 0 is for ip (again the usual one)
                    );
        
    
   /*
    * +------------------------------------------------------------------------
    * | Then we connect it to a port
    * |------------------------------------------------------------------------
    * |
    * 
    */ 
    
    printf("binding socket\n");
    
    
    //this is the datastructure that stores information about the socket
    struct sockaddr_in address;
    
    //now we configure it
    address.sin_family = AF_INET;

    address.sin_addr.s_addr = INADDR_ANY; //allow any connection (i.e. 127.0.0.1,
                                          // localhost, your ip ...)
    address.sin_port = htons( PORT );
    
    int yes = 1;//helper
    success = setsockopt(sockfd,
                             SOL_SOCKET,
                             SO_REUSEADDR, 
                             &yes, sizeof(yes)
                             );
                             
    if (success<0)
    {
        printf("setting option failed, setsockopt returned %i\n",success);
        exit(EXIT_FAILURE);
    }
    


    // now we actually connect the socket to the desired port
    success = bind(sockfd,
                       (struct sockaddr *) &address, 
                        sizeof(address)
                      );
    

    if (success<0)
    {
        printf("binding failed, bind returned %i\n",success);
        exit(EXIT_FAILURE);
    }
    
    
    
    //now we tell the socket to listen for incoming connetions
    success = listen(sockfd,
                     10 //number of simultaneus connections allowed
                    );
    
    
    //if something went wrong
    if (success<0)
    {
        printf("listening failed, listen returned %i\n",success);
        exit(EXIT_FAILURE);
    }
    
    
   /*
    * +------------------------------------------------------------------------
    * | Then we dispatch the connections
    * |------------------------------------------------------------------------
    * | Now that our server is ready to take incoming connections, we are ready 
    * | to dispatch then and hadle them individually in a separate thread
    * |
    * 
    */ 
    
    
    int live_connection; //This as well is a handle
    socklen_t addrlen = sizeof(address); // this tells the program the size of the addresss
   
   
    //TODO test multiple simultaneus connections
    for(;;)
    {
        //separate the connection to it's own port
        live_connection = accept(sockfd, (struct sockaddr *)&address, &addrlen);
        
        if(live_connection<0)
        {
            printf("Accepting failed, accept returned %i\n",live_connection);
            exit(EXIT_FAILURE);
        }
        
        
        // create a new thread to handle the request using
        // handleRequest(socket)
        pthread_t t;
        pthread_create(&t, //thread name
                       NULL, //options (nothing)
                       request_handle,//function to call
                       &live_connection //argument to the function to call
                      );
        
        //tell the operating system that when the thread ends its execution we
        //are not going to wait for it to finish, so it can free resources
        pthread_detach(t);
        
        
    }
    
    
    return 0;
}





