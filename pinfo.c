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
        char *end = NULL; // end pointer to safely handle arg
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
    printf("PID: %d\n", pid);

    //declare struct to store schedule parameters

    errno = 0;
    int policy = sched_getscheduler(pid);   //get policy
    //error handling
    if(policy == -1)
    {
        if(errno == ESRCH)
        {
            fprintf(stderr, "No such process: %d\n", pid);
            return EXIT_FAILURE;
        }
        perror("sched_getscheduler");
        return EXIT_FAILURE;
    }
    
    printf("Scheduling method:\n");
    //print policy as string
    switch(policy)
    {
        case SCHED_OTHER:
            printf("SCHED_OTHER\n"); //nice
            break;
        case SCHED_FIFO:
            printf("SCHED_FIFO\n"); // First in First Out (realtime)
            break;
        case SCHED_RR:
            printf("SCHED_RR\n"); // Round robin (realtime)
            break;
        case SCHED_BATCH:
            printf("SCHED_BATCH\n");// nice
            break;
        case SCHED_IDLE:
            printf("SCHED_IDLE\n"); //nice
            break;
        case SCHED_DEADLINE:
            printf("SCHED_DEADLINE\n"); // N/A
            break;
        default:
            printf("Unknown %d\n", policy);
            break;
    }

    
    
    //print priorty based on realtime/nice
    if(policy == SCHED_FIFO || policy == SCHED_RR) // real time 
    {
        struct sched_param sp; // declare struct to store sched_priority
        sched_getparam(pid, &sp); // pass in current pid and address of struct to store
        printf("Priority (realtime): %d\n", sp.sched_priority);
    }
    else if(policy == SCHED_DEADLINE)
    {
        printf("Priority N/A (SCHED_DEADLINE)\n");
    }
    else // nice
    {
        errno = 0;
        int nice_val = getpriority(PRIO_PROCESS, pid); // get nice value of pid
        printf("Priority (nice): %d\n", nice_val);
    }
    

    return 0;
}