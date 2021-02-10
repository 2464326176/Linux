#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>

/*
 * 多进程copy大文件
 */

/*报错并退出*/
void err_int(int ret, const char *err)
{
    if (ret == -1) {
        perror(err);
        exit(1);
    }

    return ;
}
/*报错并退出*/
void err_str(char *ret, const char *err)
{
    if (ret == MAP_FAILED) {
        perror(err);
        exit(1);
    }
}

int main(int argc, char *argv[])
{   
    int fd_src, fd_dst, ret, len, i, n;
    char *mp_src, *mp_dst, *tmp_srcp, *tmp_dstp;
    pid_t pid;

    struct stat sbuf;

    if (argc < 3 || argc > 4) {
        printf("输入规范: ./a.out 源地址 目标地址 [进程数量（可选）]\n");
        exit(1);
    } else if (argc == 3) {
        n = 5;                  //用户未指定,默认创建5个子进程
    } else if (argc == 4) {
        n = atoi(argv[3]);
    }

    fd_src = open(argv[1], O_RDONLY);
    err_int(fd_src, "打开源地址失败");

    fd_dst = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0664);
    err_int(fd_dst, "打开目标地址失败");
    ret = fstat(fd_src, &sbuf);
    err_int(ret, "fstat err");
    
    len = sbuf.st_size;
    if (len < n)
        n = len;
    ret = ftruncate(fd_dst, len);
    err_int(ret, "truncate fd_dst err");
    mp_src = (char *)mmap(NULL, len, PROT_READ, MAP_SHARED, fd_src, 0);
    err_str(mp_src, "mmap src err");
    mp_dst = (char *)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd_dst, 0);
    err_str(mp_dst, "mmap dst err");


    tmp_dstp = mp_dst;
    tmp_srcp = mp_src;
    int bs = len / n;
    int mod = len % bs;

    for (i = 0; i < n; i++) {
        if ((pid = fork()) == 0) {
            break;
        }
    }

    if (n == i) {
        for (i = 0; i < n; i++)
            wait(NULL);

    } else if (i == (n-1)){
        memcpy(tmp_dstp+i*bs, tmp_srcp+i*bs, bs+mod); 
    } else if (i == 0) {
        memcpy(tmp_dstp, tmp_srcp, bs); 
    } else {
        memcpy(tmp_dstp+i*bs, tmp_srcp+i*bs, bs); 
    }

    munmap(mp_src, len);
    munmap(mp_dst, len);

    return 0;
}
