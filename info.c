// Name, etc

// info.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
    // struct timespec ts;
    // clock_gettime(CLOCK_REALTIME, &ts);

    // printf("seconds: %ld\n", ts.tv_sec);
    char hostname[256]; // declare array with reasonable size for host name
    int result; // declare result for error handling

    //call gethostname() to retrieve host name
    result = gethostname(hostname, sizeof(hostname));
    if(result == 0)
    {
        //success
        printf("Hostname is: %s\n", hostname);
    }
    else
    {
        //fail
        printf("Error: hostname not found\n");
    }
    

}