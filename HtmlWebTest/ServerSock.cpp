//
// Created by yangfu on 2022/4/13.
//


#include "ServerSock.h"

bool ServerSock::Initsock(int port) {
    Serversock= socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in sockad;
    memset(&sockad,0,sizeof(sockad));
    sockad.sin_family=AF_INET;
    sockad.sin_port=(htons(port));
    sockad.sin_addr.s_addr= htonl(INADDR_ANY);
    if(bind(Serversock,(struct sockaddr*)(&sockad),sizeof(sockad))!=0){
        close(Serversock);
        Serversock=0;
        return false;
    }
    cout <<"bind over"<<endl;

    if(listen(Serversock,5)!=0){
        close(Serversock);
        Serversock=0;
        return false;
    }
    cout << "listen over"<<endl;
    return true;
}

bool ServerSock::Accept() {
    if((ClientSock=accept(Serversock,0,0))<=0){
        return false;
    }
    return true;
}
int ServerSock::Send(const void *buf, const int buflen) {
    return send(ClientSock,buf,buflen,0);
}
int ServerSock::Recv(void *buf, const int buflen) {
    return recv(ClientSock,buf,buflen,0);
}
ServerSock::ServerSock(){
    Serversock=0;
    ClientSock=0;
}
ServerSock::~ServerSock() {
    if(Serversock!=0){
        close(Serversock);
    }
    if(ClientSock!=0){
        close(ClientSock);
    }
}