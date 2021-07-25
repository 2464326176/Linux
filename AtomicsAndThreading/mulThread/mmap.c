#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>

void perrorLog(char *info)
{
    perror(info);
    exit(1);
}
int main()
{

    char *p = NULL;
    int fd = open("mmap.txt", O_CREAT|O_RDWR, 0644);
    if (fd < 0) {
        perrorLog("open error");
    }
    int len = ftruncate(fd, 10);
    if(len == -1) {
        perrorLog("ftruncate error");
        exit(1);
    }
    p = mmap(NULL, 10, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED) {
        perrorLog("mmap error");
    }
    strcpy(p, "yhhang");
    if(munmap(p, 10));
    close(fd);
    
    return 0;
}
