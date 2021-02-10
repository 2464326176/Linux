#ifndef MesData
#define MesData

struct MesData {
    int protocal;
    char srcname[20];
    char destname[20];
    char data[100];
};

/*
 * protocal     srcname      destname      data
 * 1            登陆者       NULL
 * 2            发送方       接收方         数据
 * 3            NULL(不在线)
 * 4            退出登陆用户（退出登陆）
 */

#endif
