#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>

/*
 Author: Shovik Shyamsundar
 Filename: reverse_copy.c
 Description: Your implementation of a program that reads in the
              content of one file and outputs the content in reverse to another file. */
 
int main(int argc, char *argv[]) {
 
  int file, reverse, filesize, n, i;
  char buf;
  
 
    if (argc != 3) {
        fprintf(stderr, "Usage %s <file> <reverse>", argv[0]);
        exit(1);
    }
 
    if ((file = open(argv[1], 0400)) < 0) { //read permission for user on file source
        fprintf(stderr, "Can't open source");
        exit(1);
    }
 
    if ((reverse = creat(argv[2], 0700)) < 0) { //rwx permission for user on reverse
        fprintf(stderr, "Can't create reverse");
        exit(1);
    }
 
    filesize = lseek(file, (off_t) 0, SEEK_END); //filesize is lastby +offset
    printf("Source file size is %d\n", filesize);
 
    for (i = filesize - 1; i > -1; i--) { //read byte by byte from end
        lseek(file, (off_t) i, SEEK_SET);
 
        n = read(file, &buf, 1);
 
        if (n != 1) {
            fprintf(stderr, "Can't read 1 byte");
            exit(1);
        }
 
        n = write(reverse, &buf, 1);
        if (n != 1) {
            fprintf(stderr, "Can't write 1 byte");
            exit(1);
        }
 
    }
    write(STDOUT_FILENO, "Program finished\n", 5);
    close(file);
    close(reverse);
 
 
 
    return 0;
}
