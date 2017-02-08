#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>

void startServer();
void trace(const char* msg);
void error(const char* msg);

int main()
{
    startServer();

    return 0;
}

void startServer()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = 9999;
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        error("Bind failed.");
    }

    if (listen(sockfd, 5) < 0)
    {
        error("Listen failed.");
    }

    for (int i = 0; i < 5; ++i)
    {
        sockaddr_in peerAddr;
        socklen_t peerAddrSize = sizeof(peerAddr);

        int peerSockfd = accept(sockfd, (sockaddr*)&peerAddr, &peerAddrSize);
        if (peerSockfd < 0)
        {
            trace("Accept failed.");
            continue;
        }

        char buff[256];
        bzero(buff, sizeof(buff));
        int readSize = read(peerSockfd, buff, 255);
        if (readSize < 0)
        {
            trace("Read failed.");
            close(peerSockfd);
            continue;
        }

        printf("Msg from client:[%s]\n", buff);

        bzero(buff, sizeof(buff));
        sprintf(buff, "This is server. Index:%02d.", i);
        int writeSize = write(peerSockfd, buff, strlen(buff));
        if (writeSize < 0)
        {
            trace("Write failed.");
            close(peerSockfd);
            continue;
        }

        close(peerSockfd);
    }

    close(sockfd);
}

void error(const char* msg)
{
    printf("%s\n", msg);
    exit(1);
}

void trace(const char* msg)
{
    printf("%s\n", msg);
}