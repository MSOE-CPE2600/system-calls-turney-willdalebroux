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
#include <time.h>

int main(int argc, char* argv[])
{

    
    if(argc != 2) // command line error handling
    {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(argc >= 2)
    {
        struct stat sb; // declare struct to store file info in
        int fd = open(argv[1], O_RDONLY | O_DIRECTORY);
        if(fd == -1)
        {
            perror("open");
            return 1;
        }
        if(fstat(fd, &sb) == -1) // pass in file desrcriptor and store/retrieve info from sb struct
        {
            perror("fstat");
            close(fd);
            return 1;
        }
        //print out file size as long long incase it's huge
        printf("File size in bytes: %lld\n", (long long) sb.st_size);
        //print UID of owner
        printf("Owner of file is: %d\n", sb.st_uid);
        //print last mod time

        time_t mod_time = sb.st_mtime; // make time variable and assign it to mod time
        struct tm *ptr = localtime(&mod_time); // declare pointer struct and convert time to local time
        
        printf("Time of last modification: %s", asctime(ptr)); // format time to string
       

        // determine type of file
        switch(sb.st_mode & S_IFMT) // deciding what type of file by masking all bits unrelated to file type
        {
            case S_IFREG:
                printf("File type is: regular file\n");
                break;
            case S_IFDIR:
                printf("File type is: directory\n");
                break;
            case S_IFCHR:
                printf("File type is: character device\n");
                break;
            case S_IFBLK:
                printf("File type is: block device\n");
                break;
            case S_IFIFO:
                printf("File type is: named pipe\n");
                break;
            case S_IFLNK:
                printf("File type is: symbolic link\n");
                break;
            case S_IFSOCK:
                printf("File type is: socket\n");
                break;
        }
        close(fd);
    }

    
     
    return 0;
}