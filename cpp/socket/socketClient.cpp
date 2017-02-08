#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <zconf.h>

void startClient();

int main()
{
    startClient();

    return 0;
}

void startClient()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    hostent* serverInfo = gethostbyname("localhost");
    sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = 9999;
    memcpy((char*)&(serverAddr.sin_addr.s_addr), serverInfo->h_addr_list[0], serverInfo->h_length);

    if (connect(sockfd, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        printf("Connect failed.\n");
        exit(1);
    }

    char buff[256];
    bzero(buff, sizeof(buff));
    sprintf(buff, "This is client.");

    int writeSize = write(sockfd, buff, strlen(buff));
    if (writeSize < 0)
    {
        printf("Write failed.\n");
        exit(1);
    }

    bzero(buff, sizeof(buff));
    int readSize = read(sockfd, buff, 255);
    if (readSize < 0)
    {
        printf("Read failed.\n");
        exit(1);
    }

    printf("Msg from server:[%s]", buff);
}