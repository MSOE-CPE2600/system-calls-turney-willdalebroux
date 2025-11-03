/***************************************************
* Will Dalebroux
* lab 9: system calls
* Section 121
***************************************************/
// pmod.c
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

    pid_t current_pid = getpid();
    printf("Current pid is: %d\n", current_pid);

    errno = 0;
    //current priority
    int nice_val = getpriority(PRIO_PROCESS, current_pid); 
    if(errno != 0)
    {
        perror("getpriority");
        return EXIT_FAILURE;
    }
    printf("Current priority is: %d\n", nice_val);
    // -20 = highest priority, 19 = lowest priority
    // nice can only lower priority
    errno = 0;
    if(setpriority(PRIO_PROCESS, current_pid, (nice_val + 10)) == -1) // lower priority to 10
    {
        perror("setpriority");
    } 
    else 
    {
        printf("Current priority is: %d\n", getpriority(PRIO_PROCESS, current_pid));    
    }
    

    /*
     * uncomment the code below to watch in htop
     * sleeps for 100seconds so you actually have time 
     * to watch program's behavior in htop
    */
    // struct timespec request = {100, 0};
    // printf("Sleeping...\n");
    // nanosleep(&request, NULL);
    //ni column shows 10 while most others show 0 or -1


    struct timespec remaining, request = {1, 837272638};
    printf("Sleeping.......\n");
    if(nanosleep(&remaining, &request) == -1) //remaining is seconds, request is nanoseconds
    {
        perror("nanosleep failed");  
    } 
    printf("Goodbye!\n");


    return 0;
}