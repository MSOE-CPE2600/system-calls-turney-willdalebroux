// Name, etc

// info.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
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