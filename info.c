/***************************************************
* Will Dalebroux
* lab 9: system calls
* Section 121
***************************************************/

// info.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#define NS_PER_SEC 1000000000ULL //nanosecond conversion; ULL to avoid overflow


int main(int argc, char* arg[])
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    /*
     *ts.tv_sec: seconds since unix epoch(12/31/1969 6:00pm CST)(1/1/1970 12:00am GMT)
     *ts.tv_nsec: how far through a nanosecond we are at any given moment
     *current time=ts.tv_sec * 1000000000ULL(unsigned long long) + ts.tv_nsec
    */
    printf("time in nanoseconds: %llu\n", (unsigned long long)((ts.tv_sec * NS_PER_SEC) + ts.tv_nsec)); 
    
    //print current time in human readable format
    time_t now = time(NULL); // hold seconds since unix epoch
    struct tm *current_time; // structure to hold seconds, minutes, hours etc.
    time(&now); // pass in address of now to get current time
    current_time = localtime(&now); //convert to local time
    printf("Current time: %s\n", asctime(current_time)); //format local time to string


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
        perror("Error: hostname not found");
    }

    struct utsname name; // declare struct to store system information in

    if(uname(&name) == 0) // pass address of struct into uname()
    {
        //success
        printf("operating system name is: %s\n", name.sysname);
        printf("operating system version is: %s\n", name.version);
        printf("operating system release is: %s\n", name.release);
        printf("hardware type identifier is: %s\n", name.machine);
    }
    else 
    {
        //fail
        perror("uname");
    }

    //get # of processors
    int processors = get_nprocs_conf(); 
    if(processors > 0)
    {
        printf("number of processors is: %d\n", processors);
    }
    else 
    {
        perror("no processors found");
    }
    

    //total ammount of physical memory
    errno = 0; // error handling
    long total_pages = sysconf(_SC_PHYS_PAGES); // 8 billion will not fit in an int so long was used
    if(total_pages == -1 && errno != 0)
    {
        perror("sysconf(_SC_PHYS_PAGES)");
    }

    errno = 0; // clear errno to prevent wrong error from being thrown
    long page_size = sysconf(_SC_PAGESIZE); // size of page in bytes
    if(page_size == -1 && errno != 0)
    {
        perror("sysconf(_SC_PAGESIZE)");
    }

    long total_mem = total_pages * page_size;
    //note: WSL only has 8gb RAM, despite thinkpad x1 having 16gb RAM
    printf("total physical memory is %lu bytes\n (%.2f Gb)\n", total_mem, total_mem / 1e9);

    // long free_mem = sysconf( _SC_AVPHYS_PAGES) * page_size; // multiply free
    errno = 0;
    if(sysconf(_SC_AVPHYS_PAGES) > 0)
    {
        long free_mem = sysconf(_SC_AVPHYS_PAGES) * page_size;
        printf("free memory is: %ld bytes\n(%.2f Gb)\n", free_mem, free_mem / 1e9);
    }
    else
    {
        perror("_SC_AVPHYS_PAGES");
    }

    
   
    

}