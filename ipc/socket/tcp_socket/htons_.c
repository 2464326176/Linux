#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    short tmp = 0x1234;

    tmp = htons(tmp);

    printf("%x", *(char *)&tmp);
    return 0;
}