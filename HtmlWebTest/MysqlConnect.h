//
// Created by yangfu on 2022/4/14.
//

#ifndef HTMLWEBTEST_MYSQLCONNECT_H
#define HTMLWEBTEST_MYSQLCONNECT_H
#include <iostream>
#include <mysql/mysql.h>
#include <cstring>
#include <map>
using namespace std;
extern map<string,string > users;
class MysqlConnect {
public:
    struct DatabaseInfo{
        string strhost;
        string strUser;
        string strPwd;
        string strDBName;
    };
    // 句柄
    MYSQL * m_pMysql;
    // 结果集
    MYSQL_RES* m_pMysqlRes;
    // 行
    MYSQL_ROW m_row;
    // field
    MYSQL_FIELD * m_pMysqlField;
    bool m_bInit;
    MysqlConnect();
    ~MysqlConnect();
    bool Init(MYSQL* mysql,const string& host,const string& user,const string& psaaworld,const string& database);
    bool QuerySql(const char* sql);


};


#endif //HTMLWEBTEST_MYSQLCONNECT_H
