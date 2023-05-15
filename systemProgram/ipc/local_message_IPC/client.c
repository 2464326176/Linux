#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "MesStruct.h"
#include "mylink.h"

#define SERVER_PROT "SEV_FIFO"

void sys_err(char *str)
{
    perror(str);
    exit(1);
}

int main(int argc, char *argv[])
{
    int server_fd, client_fd, flag, len;
    struct MesData dbuf;
    char cmdbuf[256];

    if (argc < 2) {
        printf("请输入：./client 用户名\n");
        exit(1);
    }

    if ((server_fd = open(SERVER_PROT, O_WRONLY)) < 0)
        sys_err("open");

    mkfifo(argv[1], 0777);

    struct MesData cbuf, tmpbuf, talkbuf;

    cbuf.protocal = 1;
    strcpy(cbuf.srcname,argv[1]);
    client_fd = open(argv[1], O_RDONLY|O_NONBLOCK);

    flag = fcntl(STDIN_FILENO, F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flag);

    write(server_fd, &cbuf, sizeof(cbuf));

    while (1) {
        len = read(client_fd, &tmpbuf, sizeof(tmpbuf));
        if (len > 0) {
            if (tmpbuf.protocal == 3) {
                printf("%s is not online\n", tmpbuf.destname);
            } else if (tmpbuf.protocal == 2) {
                printf("%s : %s\n", tmpbuf.srcname, tmpbuf.data);
            }
        } else if (len < 0) {
            if (errno != EAGAIN)
                sys_err("client read");
        }

        len = read(STDIN_FILENO, cmdbuf, sizeof(cmdbuf));
        if (len > 0) {
            char *dname, *databuf;
            memset(&talkbuf, 0, sizeof(talkbuf));
            cmdbuf[len] = '\0';
            //destname#data
            //B#你好
            dname = strtok(cmdbuf, "#\n");
            
            if (strcmp("exit", dname) == 0) {
                talkbuf.protocal = 4;
                strcpy(talkbuf.srcname, argv[1]);
                write(server_fd, &talkbuf, sizeof(talkbuf));
                break;
            } else {
                talkbuf.protocal = 2;
                strcpy(talkbuf.destname, dname);
                strcpy(talkbuf.srcname, argv[1]);

                databuf = strtok(NULL, "\0");               
                strcpy(talkbuf.data, databuf);
            }
            write(server_fd, &talkbuf, sizeof(talkbuf));
        }
    }

    unlink(argv[1]);
    close(client_fd);
    close(server_fd);

    return 0;
}
