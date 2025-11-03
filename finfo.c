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
        int fd = open(argv[1], O_RDONLY);
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
        //print permissions
        printf("File permissions:\n");
        printf((S_ISDIR(sb.st_mode)) ? "d" : "-"); //print d if directory, else -
        printf((sb.st_mode & S_IRUSR) ? "r" : "-"); //print r if usr has read perm, else -
        printf((sb.st_mode & S_IWUSR) ? "w" : "-"); //print w if usr has write perm, else -
        printf((sb.st_mode & S_IXUSR) ? "x" : "-"); //print x if usr has exec perm, else -
        printf((sb.st_mode & S_IRGRP) ? "r" : "-"); //print r if group has read perm, else -
        printf((sb.st_mode & S_IWGRP) ? "w" : "-"); //print w if group has write perm, else -
        printf((sb.st_mode & S_IXGRP) ? "x" : "-"); //print x if group has exec perm, else - 
        printf((sb.st_mode & S_IROTH) ? "r" : "-"); //print r if others have read perm, else -
        printf((sb.st_mode & S_IWOTH) ? "w" : "-"); //print w if others have write perm, else - 
        printf((sb.st_mode & S_IXOTH) ? "x" : "-"); //print x if others have exec perm, else -
        printf("\n");
        close(fd);
    }

    
     
    return 0;
}