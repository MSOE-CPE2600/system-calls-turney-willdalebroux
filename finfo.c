/***************************************************
* Will Dalebroux
* lab 9: system calls
* Section 121
***************************************************/

// finfo.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{

    struct stat sb; // declare struct to store file info in
    if(argc != 2) // command line error handling
    {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(argc >= 2)
    {
        int fd = open(argv[1], O_RDONLY);
        fstat(fd, &sb); // pass in file desrcriptor and store/retrieve info from sb struct
        //print out file size as long long incase it's huge
        printf("File size in bytes: %lld\n", (long long) sb.st_size);
       

    }

    
    close(fd); 
    return 0;
}