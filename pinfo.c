/***************************************************
* Will Dalebroux
* lab 9: system calls
* Section 121
***************************************************/

// pinfo.c
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>


int main(int argc, char* argv[])
{
    //determine what pid to use
    pid_t pid;
    if(argc >= 2)
    {
        char *end = NULL; //declare end pointer to safely handle arg
        errno = 0;
        long v = strtol(argv[1], &end, 10); // convert pid into long since there is no strtoi function
        //error handling
        if(errno != 0 || end == argv[1] || *end != '\0' || v <= 0 )
        {
            fprintf(stderr, "invalid PID: %s\n", argv[1]);
            return EXIT_FAILURE;
        }
        pid = (pid_t)v; // cast long to type pid_t
    }
    else 
    {
        pid = getpid();
    }
    printf("%d\n", pid);

    //get process priorty
    errno = 0;
    int policy = sched_getscheduler(pid);
    printf("Process priority: %d\n", policy);

    //set process priorty
    sched_setscheduler(pid, policy, SCHED_BATCH);
    printf("New Process priority: %d\n", policy);


    return 0;
}