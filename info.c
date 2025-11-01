// Name, etc

// info.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>


int main(int argc, char* arg[])
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
        printf("Error: sysname not found\n");
    }

    //get # of processors
    int processors = get_nprocs_conf(); 
    printf("number of processors is: %d\n", processors);

    //total ammount of physical memory
    long total_pages = sysconf(_SC_PHYS_PAGES); // 8 billion will not fit in an int so long was used
    long page_size = sysconf(_SC_PAGESIZE); // size of page in bytes

    long total_mem = total_pages * page_size;

    long free_mem = sysconf( _SC_AVPHYS_PAGES) * page_size;

    printf("total physical memory is %lu bytes\n (%.2f Gb)\n", total_mem, total_mem / 1e9);
    printf("free memory is: %ld bytes\n(%.2f Gb)\n", free_mem, free_mem / 1e9);
    

}