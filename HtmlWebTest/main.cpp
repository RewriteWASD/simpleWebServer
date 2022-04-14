#include <iostream>
#include <sys/socket.h>
#include <string>
#include <fstream>
#include "ServerSock.h"
#include <sys/sendfile.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sstream>
#include <mysql/mysql.h>
#include "MysqlConnect.h"
#include "dealPost.h"
using namespace std;

int main(){
    //mysql
    MysqlConnect mysqlobj;
    if(!mysqlobj.Init(NULL,"localhost","root","587051.","WebLogin")){
        return -1;
    }
    mysqlobj.QuerySql("select * from user_information");
    //server

    ServerSock serve;
    char serbuff[500]="HTTP/1.1 200 ok\r\nconnection: close\r\n\r\n";
    char clibuff[1024];
    if(!serve.Initsock(8088)) {
        cout << "fail sock Init" << endl;
        return -1;
    }
    while(1) {
        if (!serve.Accept()) {
            cout << "Accept fail" << endl;
            return -1;
        }
        cout << "chrome connect" << endl;
       if(serve.Recv(clibuff,sizeof(clibuff))<=0){
            cout << "recv error"<<endl;
            break;
        }
       if(clibuff[0]=='P'){
           //cout << "post"<<endl;
           cout  <<clibuff<<endl;
           char buf[520] = "HTTP/1.1 200 ok\r\nconnection: close\r\n\r\n";//HTTP响应
           int s=serve.Send(serbuff,strlen(serbuff));
           // int s1= send(serve.ClientSock, buff2, strlen(buff2), 0);
           //write(serve.ClientSock,s,strlen(buff1));
           string* sbuf= dealPost(clibuff);
           if(users.find(sbuf[0])==users.end()){
               int fd = open("/home/yangfu/CLionProjects/HtmlWebTest/test.html", O_RDONLY);
               //cout << fd<<endl;
               struct stat stat_buf;
               fstat(fd, &stat_buf);
               sendfile(serve.ClientSock, fd, NULL, stat_buf.st_size);
               close(fd);
               memset(clibuff, 0, sizeof(clibuff));
           }else {
               int fd = open("/home/yangfu/CLionProjects/HtmlWebTest/hello.html", O_RDONLY);
               //cout << fd<<endl;
               struct stat stat_buf;
               fstat(fd, &stat_buf);
               sendfile(serve.ClientSock, fd, NULL, stat_buf.st_size);
               close(fd);
               memset(clibuff, 0, sizeof(clibuff));
           }
       }else{
           cout <<"get"<<endl;
           cout  <<clibuff<<endl;
           char buf[520] = "HTTP/1.1 200 ok\r\nconnection: close\r\n\r\n";//HTTP响应
           int s=serve.Send(serbuff,strlen(serbuff));
           // int s1= send(serve.ClientSock, buff2, strlen(buff2), 0);
           //write(serve.ClientSock,s,strlen(buff1));

           int fd = open("/home/yangfu/CLionProjects/HtmlWebTest/test.html",O_RDONLY);
           //cout << fd<<endl;

           struct stat stat_buf;
           fstat(fd,&stat_buf);
           sendfile(serve.ClientSock,fd,NULL,stat_buf.st_size);
           close(fd);
           memset(clibuff,0,sizeof(clibuff));
       }

    }
    cout << "connect discoonect"<<endl;
    return 0;
}