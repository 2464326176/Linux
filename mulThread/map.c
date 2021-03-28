#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>


int main() {
    int len;
    int fd = open("test", O_RDWR | O_CREAT | O_TRUNC, 0777);
    char *p;

    len = lseek(fd, 0, SEEK_END);
    printf("%d", len);
    p = (char *)mmap(NULL, 4, PROT_READ |  PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    strcpy(p, "aaa");
    printf("%s\n", p);
    munmap(p, len);
    return 0;
}
