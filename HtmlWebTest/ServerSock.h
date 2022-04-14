//
// Created by yangfu on 2022/4/13.
//

#ifndef HTMLWEBTEST_SERVERSOCK_H
#define HTMLWEBTEST_SERVERSOCK_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <unistd.h>
using namespace std;
extern char buff2[10000];
class ServerSock {
public:
    int Serversock;
    int ClientSock;
    ServerSock();
    bool Initsock(int port);
    bool Accept();
    int Send(const void* buf,const int buflen);
    int Recv(void* buf,const int buflen);
    ~ServerSock();
};



#endif //HTMLWEBTEST_SERVERSOCK_H
