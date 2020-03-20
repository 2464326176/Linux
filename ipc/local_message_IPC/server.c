#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "MesStruct.h"
#include "mylink.h"

#define SERVER_PROT "SEV_FIFO"              /*定义众所周知的共有管道*/

mylink head = NULL;                         /*定义用户描述客户端信息的结构体*/

void sys_err(char *str)
{
    perror(str);
    exit(-1);
}

/*有新用户登录,将该用户插入链表*/
int login_qq(struct MesData *buf, mylink *head)
{
    int fd;

    fd = open(buf->srcname, O_WRONLY);
    mylink node = make_node(buf->srcname, fd);
    mylink_insert(head, node);

    return 0;
}

void transfer_qq(struct MesData *buf, mylink *head)
{
    mylink p = mylink_search(head, buf->destname);
    if (p == NULL) {
        struct MesData lineout = {3};
        strcpy(lineout.destname, buf->destname);
        mylink q = mylink_search(head, buf->srcname);
        
        write(q->fifo_fd, &lineout, sizeof(lineout));
    } else
        write(p->fifo_fd, buf, sizeof(*buf));
}

/*客户端退出*/
int logout_qq(struct MesData *buf, mylink *head)
{
    mylink p = mylink_search(head, buf->srcname);

    close(p->fifo_fd);
    mylink_delete(head, p);
    free_node(p);
}

void err_qq(struct MesData *buf)
{
    fprintf(stderr, "bad client %s connect \n", buf->srcname);
}

int main(void)
{
    int server_fd;
    struct MesData dbuf;
    
    if (access(SERVER_PROT, F_OK) != 0) {
        mkfifo(SERVER_PROT, 0664);
    }

    if ((server_fd = open(SERVER_PROT, O_RDONLY)) < 0)
        sys_err("open");

    mylink_init(&head);

    while (1) {
        read(server_fd, &dbuf, sizeof(dbuf));
        switch (dbuf.protocal) {
            case 1: login_qq(&dbuf, &head); break;      
            case 2: transfer_qq(&dbuf, &head); break;   
            case 4: logout_qq(&dbuf, &head); break;
            default: err_qq(&dbuf);
        }
    }

    close(server_fd);
}
